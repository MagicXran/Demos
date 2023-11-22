#ifndef _COMMON_DEFINE_H_
#define _COMMON_DEFINE_H_

#include <any>

#include "fmt/core.h"
#include "XMLParser.hpp"

#include "ResponseHelper.hpp"

class Common
{
public:
	Common() = delete;
	~Common() = delete;

public:

#pragma region Event Signal

	/// <summary>
	/// 状态改变事件
	/// </summary>
	inline static event_define::PRStateChangeOccuredEventHandler PRStateChangeOccured;

	/// <summary>
	/// 准备TM PDI 数据 事件
	/// </summary>
	inline static event_define::TMPDIDataReadyEventHandler  TMPDIDataReadyEvent;


	/// <summary>
	/// 数据改变事件
	/// </summary>
	inline static event_define::PRDataChangeOccuredEventHandler PRDataChangeOccured;


	inline static event_define::RecvTMMessageEventHandler RecvTMEvent;

#pragma endregion

#pragma region XML parser 

private:
	//inline static renaissance::parser::XMLParser par_;

	inline static  renaissance::parser::MsgCollectionType  RecvMessageCollectino;
	inline static  renaissance::parser::MsgCollectionType  SendMessageCollectino;

#pragma endregion


#pragma region Common functions
public:

	/// <summary>
	/// 从XML中解析接收消息队列,将其中信息缓存之内存
	/// </summary>
	/// <param name="full_path_file"></param>
	/// <param name="nodeName"></param>
	/// <returns></returns>
	inline static renaissance::parser::MsgCollectionType& ParserXMLRecvMessages(const std::string full_path_file = "", const std::string nodeName = "Link.ReceiveMessages")
	{
		try
		{
			if (RecvMessageCollectino.size() < shared_define::NonZero)
			{
				renaissance::parser::XMLParser par_;
				RecvMessageCollectino = (par_.resolveMessages(full_path_file, nodeName));
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("The error occurred in Parse ReceiveMessages XML : {0}", e.what()));
		}
		return RecvMessageCollectino;
	}


	inline static renaissance::parser::MsgCollectionType& ParserXMLSendMessages(const std::string full_path_file = "", const std::string nodeName = "Link.SendMessages")
	{
		try
		{
			if (SendMessageCollectino.size() < shared_define::NonZero)
			{
				renaissance::parser::XMLParser par_;
				SendMessageCollectino = (par_.resolveMessages(full_path_file, nodeName));
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("The error occurred in Parse SendMessages XML : {0}", e.what()));
		}
		return SendMessageCollectino;
	}




	inline static bool StateChanger(shared_define::tm_message::TMInfo& stateinfo)
	{
		const std::string& EventName = stateinfo.OtherEvent;
		const std::string& coil_id = stateinfo.Item;
		bool retval = false;
		bool stateChanged = false;
		bool subStateChanged = false;

		try
		{
			int oldState = -1;
			int oldSubState = -1;

			int newState = -1;
			int newSubState = -1;

			std::string oldStateName;
			std::string newStateName;

			//TB_PDI中唯一ID
			shared_define::ID_TYPE id_ = 0;


			auto sel_sql = uni_box::utils::string_format("select ID,IN_STATE,STATENAME, SUBSTATE, REQUEST_TYPE,PROD_REQ_TEMPLATE  from TB_PDI where COIL_ID = '%s'  order by UPDATE_TIME desc", coil_id.c_str());
			std::cout << "execute sql: " << sel_sql << std::endl;

			auto upd_sql = uni_box::utils::string_format("update TB_PDI set IN_STATE = :instate , SUBSTATE = :substate, STATENAME=:statename  where ID=:id");

			auto res = DB::OracleDB::OracleDML::executeQuery(sel_sql);
			auto conn = res.conn_;
			//conn.SetAutoCommit(true);
			int RequestType = 0;
			int prod_req_template = 101;
			ocilib::Statement stmt(conn);

			if (res.rs_.Next())
			{
				// Memorize old state and substate
				oldState = res.rs_.Get<int>("IN_STATE");
				oldSubState = res.rs_.Get<int>("SUBSTATE");
				oldStateName = res.rs_.Get<std::string>("STATENAME");

				newState = oldState;
				newSubState = oldSubState;
				newStateName = oldStateName;

				id_ = res.rs_.Get<shared_define::ID_TYPE>("ID");
				RequestType = res.rs_.Get<int>("REQUEST_TYPE");
				prod_req_template = res.rs_.Get<int>("PROD_REQ_TEMPLATE");


#pragma region TM PDI Data Request
				if (EventName == "TM PDI Data Request")
				{
					// Check conditions for unremove
					if (oldStateName == shared_define::OrderStateTypes::OrderIsFinished &&
						oldSubState == (int)shared_define::SubStatesEnum::IsRejected
						)
					{
						// Unremove: Set state to Released
						newStateName = shared_define::OrderStateTypes::OrderIsReleased;
						newState = (int)shared_define::OrderStatesEnum::OrderIsReleased;
						newSubState = (int)shared_define::SubStatesEnum::AsInitial;

						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}，upd_sql：{1}", EventName, upd_sql));
						}

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}

						stateChanged = true;
						subStateChanged = true;

						retval = true;
					}
				}
#pragma endregion

#pragma region  PDI Data Acknowledge
				else if (EventName == "PDI Data Acknowledge")
				{
					// Check conditions for unremove 
					if (oldStateName == shared_define::OrderStateTypes::OrderIsDraft ||
						oldStateName == shared_define::OrderStateTypes::OrderIsReleased
						)
					{
						// Set state to Dispatched if not already
						if (shared_define::OrderStateTypes::OrderIsDispatched != oldStateName)
						{
							newState = (int)shared_define::OrderStatesEnum::OrderIsDispatched;
							newStateName = shared_define::OrderStateTypes::OrderIsDispatched;

							stateChanged = true;

							try
							{
								stmt.Prepare(upd_sql);
								stmt.Bind(":instate", newState, ocilib::BindInfo::In);
								stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
								stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
								stmt.Bind(":id", id_, ocilib::BindInfo::In);
								stmt.ExecutePrepared();
								conn.Commit();
							}
							catch (...)
							{
								conn.Rollback();
								logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));
							}
						}


						// Update response and raise event if a change has occured.
						if (stateChanged)
						{
							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}

					}

					retval = true;
				}
#pragma endregion

#pragma region  TM Production Start
				else if (EventName == "TM Production Start")
				{
					//TODO: 考虑使用Oracle JOB 实现 ++
					// Started++;

					 // Set state to InProduction if not already
					if (shared_define::OrderStateTypes::OrderInProduction != oldStateName)
					{
						newStateName = shared_define::OrderStateTypes::OrderInProduction;
						newState = (int)shared_define::OrderStatesEnum::OrderInProduction;
						stateChanged = true;

						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));
						}
					}

					{
						// Update response and raise event if a change has occurred.
						if (stateChanged)
						{
							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}

					}
					retval = true;
				}
#pragma endregion

#pragma region TM Finished

				else if (EventName == "TM Finished")
				{
					// Set substate to Completed if not already and not Rejected
					if (oldSubState != (int)shared_define::SubStatesEnum::IsCompleted ||
						oldSubState < (int)shared_define::SubStatesEnum::IsRejected
						)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsCompleted;
						subStateChanged = true;
					}

					// Set state to Finished if not already
					if (oldState != (int)shared_define::OrderStatesEnum::OrderIsFinished)
					{
						if (oldStateName != shared_define::OrderStateTypes::OrderIsFinished)
						{
							newStateName = shared_define::OrderStateTypes::OrderIsFinished;
							newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
							stateChanged = true;
						}
					}

					try
					{
						stmt.Prepare(upd_sql);
						stmt.Bind(":instate", newState, ocilib::BindInfo::In);
						stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
						stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
						stmt.Bind(":id", id_, ocilib::BindInfo::In);
						stmt.ExecutePrepared();
						conn.Commit();
					}
					catch (...)
					{
						conn.Rollback();
						logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));
					}

					{
						// Update response and raise event if a change has occured.
						if (stateChanged || subStateChanged)
						{
							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}

					}

					retval = true;
				}

#pragma endregion

#pragma region	TM Rejected

				else if (EventName == "TM Rejected")
				{

					// Set substate to Completed if not already
					if (oldSubState != (int)shared_define::SubStatesEnum::IsRejected)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsRejected;
						subStateChanged = true;
					}

					// Set state to Finished if not already
					if (oldStateName != shared_define::OrderStateTypes::OrderIsFinished)
					{
						newStateName = shared_define::OrderStateTypes::OrderIsFinished;
						newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
						stateChanged = true;
					}

					try
					{
						stmt.Prepare(upd_sql);
						stmt.Bind(":instate", newState, ocilib::BindInfo::In);
						stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
						stmt.Bind(":id", id_, ocilib::BindInfo::In);
						stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
						stmt.ExecutePrepared();
						conn.Commit();
					}
					catch (...)
					{
						conn.Rollback();
						logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));
					}

					{
						// Update response and raise event if a change has occured.
						if (stateChanged || subStateChanged)
						{
							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}

					}

					retval = true;
				}

#pragma endregion

#pragma region	TM Forced Delete

				else if (EventName == "TM Forced Delete")
				{

					// Set substate to Completed if not already and not Rejected
					if (oldSubState != (int)shared_define::SubStatesEnum::IsCompleted ||
						oldSubState < (int)shared_define::SubStatesEnum::IsRejected
						)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsCompleted;
						subStateChanged = true;
					}

					// Set state to Finished if not already
					if (oldStateName != shared_define::OrderStateTypes::OrderIsFinished)
					{
						newStateName = shared_define::OrderStateTypes::OrderIsFinished;
						newState = shared_define::OrderStatesEnum::OrderIsFinished;
						stateChanged = true;
					}


					try
					{
						stmt.Prepare(upd_sql);
						stmt.Bind(":instate", newState, ocilib::BindInfo::In);
						stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
						stmt.Bind(":id", id_, ocilib::BindInfo::In);
						stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
						stmt.ExecutePrepared();
						conn.Commit();
					}
					catch (...)
					{
						conn.Rollback();
						logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

					}

					{
						// Update response and raise event if a change has occured.
						if (stateChanged || subStateChanged)
						{
							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}

					}

					retval = true;
				}

#pragma endregion

#pragma region	Tracking Zone Event

				else if (EventName == "Tracking Zone Event")
				{

#pragma region Material enters zone

					if (stateinfo.EventType == (int)shared_define::tm_message::TrackEvent::Entry)
					{

#pragma region Synchronization Zone
						if (stateinfo.ZoneName == "SY")
						{
							retval = true;
						}
#pragma endregion

#pragma region Furnace Zone (recharge)
						if ((
							stateinfo.ZoneName == "FU1" ||
							stateinfo.ZoneName == "FU2" ||
							stateinfo.ZoneName == "FU3") &&
							stateinfo.Gate == 21)// mill side
						{
							// Set substate to IsCharged if not already
							if (oldSubState != (int)shared_define::SubStatesEnum::IsCharged)
							{
								newSubState = (int)shared_define::SubStatesEnum::IsCharged;
								subStateChanged = true;
							}

							if (subStateChanged)
							{
								try
								{
									stmt.Prepare(upd_sql);
									stmt.Bind(":instate", newState, ocilib::BindInfo::In);
									stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
									stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
									stmt.Bind(":id", id_, ocilib::BindInfo::In);
									stmt.ExecutePrepared();
									conn.Commit();
								}
								catch (...)
								{
									conn.Rollback();
									logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

								}

							}
						}

#pragma endregion

#pragma region Coil Banding Machine Zones

						if (stateinfo.ZoneName == "CH1CBM" ||
							stateinfo.ZoneName == "CH2CBM" ||
							stateinfo.ZoneName == "CH3CBM"
							)
						{
							// Ghost orders handled with FM Roll End PDLog
							if (RequestType == (int)shared_define::mes_message::ReqTypesEnum::ProductionOrder)
							{
								// Set substate to IsRolled if not already
								if (oldSubState != (int)shared_define::SubStatesEnum::IsRolled &&
									oldSubState < (int)shared_define::SubStatesEnum::IsRejected)
								{
									newSubState = (int)shared_define::SubStatesEnum::IsRolled;
									subStateChanged = true;
								}

								if (subStateChanged)
								{
									try
									{
										stmt.Prepare(upd_sql);
										stmt.Bind(":instate", newState, ocilib::BindInfo::In);
										stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
										stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
										stmt.Bind(":id", id_, ocilib::BindInfo::In);
										stmt.ExecutePrepared();
										conn.Commit();
									}
									catch (...)
									{
										conn.Rollback();
										logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));
									}

									if (PRStateChangeOccured)
									{
										PRStateChangeOccured(id_);
									}

								}
								retval = true;
							}
						}
#pragma endregion

#pragma region Strip Transfer Car

						else if (stateinfo.ZoneName == "STC")
						{
							// Plate orders are finished when the transfer bar is moved to STC
							if (prod_req_template == (int)shared_define::mes_message::ReqTemplateEnum::Plate)
							{
								// Set substate to Completed if not already and not rejected
								if (oldSubState != (int)shared_define::SubStatesEnum::IsCompleted &&
									oldSubState < (int)shared_define::SubStatesEnum::IsRejected)
								{
									newSubState = (int)shared_define::SubStatesEnum::IsCompleted;
									subStateChanged = true;
								}

								// Set state to Finished if not already
								if (shared_define::OrderStateTypes::OrderIsFinished != oldStateName)
								{
									newStateName = shared_define::OrderStateTypes::OrderIsFinished;
									newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
									stateChanged = true;
								}

								try
								{
									stmt.Prepare(upd_sql);
									stmt.Bind(":instate", newState, ocilib::BindInfo::In);
									stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
									stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
									stmt.Bind(":id", id_, ocilib::BindInfo::In);
									stmt.ExecutePrepared();
									conn.Commit();
								}
								catch (...)
								{
									conn.Rollback();
									logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

								}

								if (stateChanged || subStateChanged)
								{
									if (PRStateChangeOccured)
									{
										PRStateChangeOccured(id_);
									}
								}
								retval = true;
							}
						}
#pragma endregion

#pragma region Other Zones

						// Normal situation as all zone events do not change state/substate.
						else
						{
							retval = true;
						}
#pragma endregion


					}
#pragma endregion

#pragma region Material exits zone

					else if (stateinfo.EventType == (int)shared_define::tm_message::TrackEvent::Exit)
					{
						retval = true;
					}
#pragma endregion


#pragma region Material is removed from zone

					else if (stateinfo.EventType == (int)shared_define::tm_message::TrackEvent::Remove)
					{
						// Set the state to finished if not already when
							   // a material is removed as Finished.
						if (stateinfo.TMStatus == (int)shared_define::tm_message::TrackRemoveReason::Finished_)
						{
							// Set substate to Completed if not already and not rejected
							if (oldSubState != (int)shared_define::SubStatesEnum::IsCompleted &&
								oldSubState < (int)shared_define::SubStatesEnum::IsRejected)
							{
								newSubState = (int)shared_define::SubStatesEnum::IsCompleted;
								subStateChanged = true;
							}

							// Set state to Finished if not already
							if (shared_define::OrderStateTypes::OrderIsFinished != oldStateName)
							{
								//TODO: newState.Completed++;
								newStateName = shared_define::OrderStateTypes::OrderIsFinished;
								newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
								stateChanged = true;
							}

							if (stateChanged || subStateChanged)
							{
								try
								{
									stmt.Prepare(upd_sql);
									stmt.Bind(":instate", newState, ocilib::BindInfo::In);
									stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
									stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
									stmt.Bind(":id", id_, ocilib::BindInfo::In);
									stmt.ExecutePrepared();
									conn.Commit();
								}
								catch (...)
								{
									conn.Rollback();
									logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

								}
							}
						}

						// Set the state to rejected if not already when
							   // a material is removed as Scrapped.
						else if (stateinfo.TMStatus == (int)shared_define::tm_message::TrackRemoveReason::Scrapped_)
						{
							// Set substate to IsRejected if not already
							if (oldSubState != (int)shared_define::SubStatesEnum::IsRejected)
							{
								newSubState = (int)shared_define::SubStatesEnum::IsRejected;
								subStateChanged = true;
							}

							// Set state to Finished if not already
							if (shared_define::OrderStateTypes::OrderIsFinished != oldStateName)
							{
								newStateName = shared_define::OrderStateTypes::OrderIsFinished;
								newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
								stateChanged = true;
							}

							if (stateChanged || subStateChanged)
							{
								try
								{
									stmt.Prepare(upd_sql);
									stmt.Bind(":instate", newState, ocilib::BindInfo::In);
									stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
									stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
									stmt.Bind(":id", id_, ocilib::BindInfo::In);
									stmt.ExecutePrepared();
									conn.Commit();
								}
								catch (...)
								{
									conn.Rollback();
									logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

								}

								if (PRStateChangeOccured)
								{
									PRStateChangeOccured(id_);
								}
							}

						}
						retval = true;

					}
#pragma endregion

#pragma region Material is inserted in zone

					else if (stateinfo.EventType == (int)shared_define::tm_message::TrackEvent::Insert)
					{
						if (oldStateName == shared_define::OrderStateTypes::OrderIsFinished &&
							oldSubState == (int)shared_define::SubStatesEnum::IsRejected
							)
						{
							// Unremove: Set state to Released
							newStateName = shared_define::OrderStateTypes::OrderInProduction;
							newState = (int)shared_define::OrderStatesEnum::OrderInProduction;
							newSubState = GetSubstateByZoneName(stateinfo.ZoneName);

							stateChanged = true;
							subStateChanged = true;
						}

						if (stateChanged)
						{
							try
							{
								stmt.Prepare(upd_sql);
								stmt.Bind(":instate", newState, ocilib::BindInfo::In);
								stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
								stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
								stmt.Bind(":id", id_, ocilib::BindInfo::In);
								stmt.ExecutePrepared();
								conn.Commit();
							}
							catch (...)
							{
								conn.Rollback();
								logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

							}

							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}

						retval = true;

					}
#pragma endregion

#pragma region Other event types

					// Normal situation as all zone events do not change state/substate.
					else
					{
						retval = true;
					}
#pragma endregion
				}

#pragma endregion

#pragma region FCE Charged

				else if (EventName == "FCE Charged")
				{
					// Set substate to Charged if not already
					if (oldSubState != (int)shared_define::SubStatesEnum::IsCharged)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsCharged;
						subStateChanged = true;

						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}
					}

					// Update response and raise event if a change has occured
					if (subStateChanged)
					{

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}
					}

					return true;
				}

#pragma endregion

#pragma region FCE Discharged

				else if (EventName == "FCE Discharged")
				{
					// Set substate to Charged if not already
					if (oldSubState != (int)shared_define::SubStatesEnum::IsDischarged)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsDischarged;
						subStateChanged = true;
					}

					// Update response and raise event if a change has occured
					if (subStateChanged)
					{
						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}
					}

					return true;
				}

#pragma endregion

#pragma region FCE Next To Discharge

				else if (EventName == "FCE Next To Discharge")
				{
					// Set substate to Next To Discharge if not already
					if ((int)shared_define::SubStatesEnum::IsNextToDischarge != oldSubState)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsNextToDischarge;
						subStateChanged = true;
					}

					// Update response and raise event if a change has occured.
					if (subStateChanged)
					{
						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}
					}
					retval = true;
				}
#pragma endregion

#pragma region RM1 Start Rolling

				else if (EventName == "RM1 Start Rolling")
				{
					// Set substate to InRM1Rolling if not already
					if ((int)shared_define::SubStatesEnum::InRM1Rolling != oldSubState)
					{
						newSubState = (int)shared_define::SubStatesEnum::InRM1Rolling;
						subStateChanged = true;
					}

					// Update response and raise event if a change has occured.
					if (subStateChanged)
					{
						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}
					}
					retval = true;

				}

#pragma endregion

#pragma region RM2 Start Rolling

				else if (EventName == "RM2 Start Rolling")
				{
					// Set substate to InRM2Rolling if not already
					if ((int)shared_define::SubStatesEnum::InRM2Rolling != oldSubState)
					{
						newSubState = (int)shared_define::SubStatesEnum::InRM2Rolling;
						subStateChanged = true;
					}

					// Update response and raise event if a change has occured.
					if (subStateChanged)
					{
						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}
					}
					retval = true;

				}
#pragma endregion

#pragma region FM Start Rolling

				else if (EventName == "FM Start Rolling")
				{
					// Set substate to InRM2Rolling if not already
					if ((int)shared_define::SubStatesEnum::InFMRolling != oldSubState)
					{
						newSubState = (int)shared_define::SubStatesEnum::InFMRolling;
						subStateChanged = true;
					}

					// Update response and raise event if a change has occured.
					if (subStateChanged)
					{
						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}
					}
					retval = true;

				}
#pragma endregion

#pragma region Coil Finished

				else if (EventName == "Coil Finished")
				{

					// Differenet handling require for Production Orders
					// and Ghost Orders.
					if (RequestType == (int)shared_define::mes_message::ReqTypesEnum::GhostOrder)
					{
						// Set substate to InRM2Rolling if not already
						if ((int)shared_define::SubStatesEnum::IsCompleted != oldSubState &&
							oldSubState < (int)shared_define::SubStatesEnum::IsRejected)
						{
							newSubState = (int)shared_define::SubStatesEnum::IsCompleted;
							subStateChanged = true;
						}

						// Set state to Finished if not already
						if (shared_define::OrderStateTypes::OrderIsFinished != oldStateName)
						{
							stateChanged = true;
							newStateName = shared_define::OrderStateTypes::OrderIsFinished;
							newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
						}

						try
						{
							stmt.Prepare(upd_sql);
							stmt.Bind(":instate", newState, ocilib::BindInfo::In);
							stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
							stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
							stmt.Bind(":id", id_, ocilib::BindInfo::In);
							stmt.ExecutePrepared();
							conn.Commit();
						}
						catch (...)
						{
							conn.Rollback();
							logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

						}


						// Update response and raise event if a change has occured.
						if (subStateChanged || stateChanged)
						{

							if (PRStateChangeOccured)
							{
								PRStateChangeOccured(id_);
							}
						}
						retval = true;
					}
					else
					{
						// Production order handled elsewhere
					}

					retval = true;
				}
#pragma endregion

#pragma region Production End

				else if (EventName == "Production End")
				{

					// Set substate to Completed if not already
					if ((int)shared_define::SubStatesEnum::IsCompleted != oldSubState &&
						oldSubState < (int)shared_define::SubStatesEnum::IsRejected)
					{
						newSubState = (int)shared_define::SubStatesEnum::IsCompleted;
						subStateChanged = true;
					}

					// Set state to Finished if not already
					if (shared_define::OrderStateTypes::OrderIsFinished != oldStateName)
					{
						stateChanged = true;
						newStateName = shared_define::OrderStateTypes::OrderIsFinished;
						newState = (int)shared_define::OrderStatesEnum::OrderIsFinished;
					}

					try
					{
						stmt.Prepare(upd_sql);
						stmt.Bind(":instate", newState, ocilib::BindInfo::In);
						stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
						stmt.Bind(":statename", newStateName, newStateName.size(), ocilib::BindInfo::In);
						stmt.Bind(":id", id_, ocilib::BindInfo::In);
						stmt.ExecutePrepared();
						conn.Commit();
					}
					catch (...)
					{
						conn.Rollback();
						logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

					}

					// Update response and raise event if a change has occured.
					if (subStateChanged || stateChanged)
					{

						if (PRStateChangeOccured)
						{
							PRStateChangeOccured(id_);
						}
					}
					retval = true;
				}
#pragma endregion
			}
			else
			{
				// ProductionRequest does not exist!
				logger_.Error(fmt::format("StateCheck failed for matId '{0}', Item not found!", coil_id));

				retval = false;
			}


			// Self-correct order state: catch up to PRD if at least charged
			if (newSubState >= (int)shared_define::SubStatesEnum::IsCharged &&
				(newStateName == shared_define::OrderStateTypes::OrderIsDispatched ||
				newStateName == shared_define::OrderStateTypes::OrderIsReleased ||
				newStateName == shared_define::OrderStateTypes::OrderIsDraft))
			{
				newStateName = shared_define::OrderStateTypes::OrderInProduction;
				newState = (int)shared_define::OrderStatesEnum::OrderInProduction;

				try
				{
					stmt.Prepare(upd_sql);
					stmt.Bind(":instate", newState, ocilib::BindInfo::In);
					stmt.Bind(":substate", newSubState, ocilib::BindInfo::In);
					stmt.Bind(":id", id_, ocilib::BindInfo::In);
					stmt.ExecutePrepared();
					conn.Commit();
				}
				catch (...)
				{
					conn.Rollback();
					logger_.Error(fmt::format("ExecutePrepared failed ! EventName={0}", EventName));

				}
			}

		}
		catch (const std::exception& e)
		{
			logger_.Error(fmt::format("Changing state/substate failed for matId: {0} ,reason:{1}", coil_id, e.what()));

			retval = false;
		}

		return retval;
	}


	inline static int GetSubstateByZoneName(const std::string& zoneName)
	{
		using namespace  shared_define::tm_message;
		int z = shared_define::tm_message::ZoneName_Value[zoneName];
		if (z == ZonesEnum::FUENW || z == ZonesEnum::FU1ENRT || z == ZonesEnum::FU2ENRT ||
			z == ZonesEnum::FU3ENRT) return (int)shared_define::SubStatesEnum::AsInitial;
		else if (z < ZonesEnum::FRRT) return (int)shared_define::SubStatesEnum::IsCharged;
		else if (z < ZonesEnum::RM1) return (int)shared_define::SubStatesEnum::IsDischarged;
		else if (z < ZonesEnum::RM2) return (int)shared_define::SubStatesEnum::InRM1Rolling;
		else if (z < ZonesEnum::FM) return (int)shared_define::SubStatesEnum::InRM2Rolling;
		else if (z < ZonesEnum::WB1) return (int)shared_define::SubStatesEnum::InFMRolling;
		else return (int)shared_define::SubStatesEnum::IsRolled;
	}



	/// <summary>
	/// 保存信息于ACTUAL_RESPONSES
	/// 先判断TB_PDI中是否存在该记录，若不存在则退出；
	/// 存在，则根据id判断ACTUAL_RESPONSES中是否存在该记录：
	/// 若存在，则更新
	/// 不存在则创建记录
	/// </summary>
	inline static void HandleTMRemove(shared_define::tm_message::TMInfo& tmInfo)
	{
		// Set the reject location to unknown
		int rejectLocation = 0; //吊销位置 0：炉前，1：炉后
		int equipId = 0;
		try
		{
			// Save reject data if a reject was detected
			if (tmInfo.TMStatus == (int)shared_define::tm_message::TrackRemoveReason::Scrapped_)
			{
				// Get Equipment Id for the reject data 1005
				equipId = ActualResponseFlyw::CacheEquipNameId()[shared_define::EquipNames::REJ_DATA];

				auto res_pdi = DB::OracleDB::OracleDML::executeQuery(uni_box::utils::string_format("select ID from tb_pdi where coil_id ='%s' ", tmInfo.Item.c_str()));

				try
				{
					if (res_pdi.rs_.Next())
					{
						auto pdi_id = res_pdi.rs_.Get<shared_define::ID_TYPE>("ID");

						if (tmInfo.ZoneName == "SegReqEvent")
						{
							// Check if reject data has already been saved in which case we quit
							if (ActualResponseFlyw::FindOne(pdi_id, shared_define::EquipNames::REJ_DATA, shared_define::PropNames::REJECT_LOCATION, 0) != nullptr)
								return;

							// Set the reject location to unknown
							rejectLocation = 0;

							// ZoneName = "SegReqEvent" not useful for an operator
							tmInfo.ZoneName.clear();
						}
						else
						{
							rejectLocation = GetRejectLocation(tmInfo);
						}

#pragma region  Save REJECT LOCATION
						try
						{
							shared_define::ComInfo rejInfo{ shared_define::PropNames::REJECT_LOCATION,shared_define::PropNames::REJECT_LOCATION, std::to_string(rejectLocation) };
							ResponseHelper::SaveActualResponse(pdi_id, equipId, rejInfo);

						}
						catch (const std::exception& e)
						{
							logger_.Error(fmt::format("Failed to save '{0}' for item '{1}'! reason:{2}", shared_define::PropNames::REJECT_LOCATION, tmInfo.Item, e.what()));
						}
#pragma endregion

#pragma region  Save REJECT ZONE
						try
						{
							shared_define::ComInfo rejInfo{ shared_define::PropNames::REJECT_ZONE,shared_define::PropNames::REJECT_ZONE,tmInfo.ZoneName };
							ResponseHelper::SaveActualResponse(pdi_id, equipId, rejInfo);

						}
						catch (const std::exception& e)
						{
							logger_.Error(fmt::format("Failed to save '{0}' for item '{1}'! reason:{2}", shared_define::PropNames::REJECT_LOCATION, tmInfo.Item, e.what()));
						}
#pragma endregion

#pragma region 其余的吊销信息默认均为空

#pragma endregion

					}
					else
					{

						throw std::logic_error(uni_box::utils::string_format("Coil_ID {%s} does not exist in TB_PDI!", tmInfo.Item.c_str()));
					}

				}
				catch (const std::exception& e)
				{
					throw std::logic_error(uni_box::utils::string_format("处理吊销数据时出错 Coil_ID {%s}, reason: {%s}", tmInfo.Item.c_str(), e.what()));
				}
			}
		}
		catch (const std::exception& e)
		{
			throw e;
		}
	}

	/// <summary>
	///  Helper method to determine the customer specified reject location.
	///  The following areas are defined:
	///  1 = Before furnaces
	///  2 = Between furnaces and RM1
	///  3 = Between RM1 and RM2 (including RM1)
	///  4 = Between RM2 and FM Stand 1 (including RM2)
	///  5 = Between FM Stand 1 and FM Stand 7 (including coil box?)
	///  6 = After FM Stand 7</summary>
	/// <param name="tmInfo"></param>
	/// <returns>An integer defining the area where the reject occured.</returns>
	inline static int GetRejectLocation(const shared_define::tm_message::TMInfo& tmInfo)
	{
		int rejLoc = 0;
		int zoneNo = 0;

		if (shared_define::tm_message::ZoneName_Value.find(tmInfo.ZoneName) == shared_define::tm_message::ZoneName_Value.end())
		{
			throw std::logic_error(fmt::format("Zone name not defined in ZonesEnum - '{0}'!", tmInfo.ZoneName));
		}

		zoneNo = shared_define::tm_message::ZoneName_Value[tmInfo.ZoneName];

		if (zoneNo < (int)shared_define::tm_message::ZonesEnum::FU3)
			rejLoc = 1;
		else if (zoneNo < (int)shared_define::tm_message::ZonesEnum::RM1)
			rejLoc = 2;
		else if (zoneNo < (int)shared_define::tm_message::ZonesEnum::RM2)
			rejLoc = 3;
		else if (zoneNo < (int)shared_define::tm_message::ZonesEnum::FM)
			rejLoc = 4;
		else if (zoneNo == (int)shared_define::tm_message::ZonesEnum::FM)
			rejLoc = 5;
		else if (zoneNo > (int)shared_define::tm_message::ZonesEnum::FM)
			rejLoc = 6;

		return rejLoc;
	}

	/// <summary>
	///  在特定模式下生成指定长度的字符串.
	/// </summary>
	/// <param name="src">以null结尾的字符串</param>
	/// <param name="dst">指定长度N的字符，可以没有以null结尾。</param>
	/// <param name="mode">模式切换：1 => 左补零,数字数据：则在不满位数时左补 0; 2 => 右补空格,字符串数据：则在不够长度时右补空格 </param>
	/// <returns>dst</returns>
	template<int N>
	inline static char* GenerateRuleStr(const char* src, char* dst, unsigned short mode)
	{
		size_t src_len = strlen(src);
		if (src_len < 1)
		{
			throw std::invalid_argument("src length is null !");
		}

		memset(dst, 0x00, N);

		//mode: 1 => 左补零,数字数据：则在不满位数时左补 0
		if (mode == 1)
		{
			char temp_[N];
			memset(temp_, '0', sizeof(temp_));

			if (src_len <= N)
			{
				size_t delta_len = N - src_len;
				memcpy(temp_ + delta_len, src, src_len);
				memcpy(dst, temp_, N);
				return dst;
			}
			else
				throw std::invalid_argument("Src length is greater than n !");
		}
		//mode: 2 => 右补空格,字符串数据：则在不够长度时右补空格
		else if (mode == 2)
		{
			char temp_[N];
			memset(temp_, ' ', sizeof(temp_));

			if (src_len <= N)
			{
				size_t delta_len = N - src_len;
				memcpy(temp_, src, src_len);
				memcpy(dst, temp_, N);
				return dst;
			}
			else
				throw std::invalid_argument("Src length is greater than n !");
		}
		else
		{
			throw std::invalid_argument("Unknow mode !");
		}
	}


	/// <summary>
	/// 查询指定公差，一般查表TGT_TOLERANCE
	/// 一些之为定值，参考ABB L2
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="item_name"></param>
	/// <returns></returns>
	inline static std::string  InquiryTolerance(const std::string& item_name, const std::string& defalut_value, const std::string& descr)
	{
		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery(uni_box::utils::string_format("select VALUE from SYSPARAM where NAME='%s'", item_name.c_str()));

			if (!res.rs_.Next())
			{
				DB::OracleDB::OracleDML::execute(fmt::format("insert into SYSPARAM (name, value,DESCR) values ('{0}','{1}','{2}')", item_name, defalut_value, descr));

				return defalut_value;
			}

			return  res.rs_.Get<std::string>("VALUE");
		}
		catch (const std::exception& e)
		{
			throw e;
		}
	}


	/// <summary>
	/// 决定是否使用测量值
	/// </summary>
	/// <param name="measVal"></param>
	/// <param name="tolerance"></param>
	/// <param name="pdiVal"></param>
	/// <returns></returns>
	template<typename T>
	inline static bool IsMeasuredValueOK(T measVal, T tolerance, T pdiVal)
	{
		// Return false if the measured value is outside the tolerances
		if (measVal > pdiVal + tolerance * pdiVal / 100)
			return false;
		else if (measVal < pdiVal - tolerance * pdiVal / 100)
			return false;

		return true;
	}


	/// <summary>
	/// 根据ABB 规则，使字段值符合规约
	/// </summary>
	/// <param name="value"></param>
	/// <param name="type"></param>
	/// <returns></returns>
	inline static const std::string ValueEncode(char* value, int type)
	{
		std::string buffer;
		switch (type)
		{

			case (int)shared_define::ValueType::B:
			{
				//TODO: 待确认逻辑
				if (std::stoi(value))
				{
					buffer.append(19, '0').append("1").append("E000");
					return buffer;
				}
				else
				{
					buffer.append(19, '0').append("0").append("E000");
					return buffer;
				}
			}
			case (int)shared_define::ValueType::D:
			{
				// The DateTime format in the string: "YYYY-MM-DD HH:MM:SS"
				// ((DateTime)value).ToString("yyyy-MM-dd HH:mm:ss").PadRight(20, ' ') + "E" + "000";
				buffer.append(value);
				auto n_ = 20 - strlen(value);
				buffer.append(n_, ' ').append("E000");
				return buffer;
			}
			case (int)shared_define::ValueType::I:
			{

				int n_ = 20 - strlen(value);
				if (n_ < 0)
				{
					throw std::invalid_argument("value's length is more than 20 !");
				}

				buffer.append(n_, '0');
				buffer.append(value);
				buffer.append("E000");
				return buffer;

			}
			case (int)shared_define::ValueType::R:
			{
				return ToScientific(value, 2);
			}
			case (int)shared_define::ValueType::T:
			{
				buffer = value;

				auto n_ = 20 - buffer.size();
				if (n_ < 0)
				{
					throw std::invalid_argument("value's length is more than 20 !");
				}
				buffer.append(n_, ' ');
				buffer.append("E000");
				return buffer.c_str();
			}
			break;
			default:
			throw std::invalid_argument("Invalid data type");
		}
	}

	/// <summary>
	/// Data type I = integer, R= real, B= boolean, T= Text (20 char)
	/// </summary>
	/// <param name="value"></param>
	/// <param name="type"></param>
	/// <returns></returns>
	inline static const std::string ValueEncode(std::string value, int type)
	{
		try
		{
			switch (type)
			{

				case (int)shared_define::ValueType::B:
				{
					//TODO: 待确认逻辑
					if (std::stoi(value))
					{
						return uni_box::utils::PadLeft("1", 20, '0').append("E000");
					}
					else
					{
						return uni_box::utils::PadLeft("0", 20, '0').append("E000");
					}
				}
				break;

				case (int)shared_define::ValueType::D:
				{
					// The DateTime format in the string: "YYYY-MM-DD HH:MM:SS"
					// ((DateTime)value).ToString("yyyy-MM-dd HH:mm:ss").PadRight(20, ' ') + "E" + "000";
					return uni_box::utils::PadRight(value, 20, ' ').append("E000");
				}
				break;
				case (int)shared_define::ValueType::I:
				{
					return uni_box::utils::PadLeft(value, 20, '0').append("E000");
				}
				break;
				case (int)shared_define::ValueType::R:
				{
					return ToScientific(value, 2);
				}
				break;
				case (int)shared_define::ValueType::T:
				{
					return uni_box::utils::PadRight(value, 20, ' ').append("E000");
				}
				break;

				default:
				throw std::invalid_argument("Invalid data type");
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Error in ValueEncode(), reason:{}", e.what()));
		}
	}



	inline static const std::string ValueEncode(std::string value, const std::string& type)
	{
		try
		{

			if (type == "B")
			{
				//TODO: 待确认逻辑
				if (std::stoi(value))
				{
					return uni_box::utils::PadLeft("1", 20, '0').append("E000");
				}
				else
				{
					return uni_box::utils::PadLeft("0", 20, '0').append("E000");
				}
			}

			else if (type == "D")
			{
				// The DateTime format in the string: "YYYY-MM-DD HH:MM:SS"
				// ((DateTime)value).ToString("yyyy-MM-dd HH:mm:ss").PadRight(20, ' ') + "E" + "000";
				return uni_box::utils::PadRight(value, 20, ' ').append("E000");
			}

			else if (type == "I")
			{
				return uni_box::utils::PadLeft(std::to_string(std::stoi(value)), 20, '0').append("E000");
			}
			else if (type == "R")
			{
				return ToScientific(value, 2);
			}
			else if (type == "T")
			{
				return uni_box::utils::PadRight(value, 20, ' ').append("E000");
			}
			else
			{
				throw std::invalid_argument("Invalid data type");
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Error in ValueEncode(), reason:{}", e.what()));
		}
	}

	/// <summary>
	/// 将浮点数转为科学计数法（ABB规则的科学计数法）：00000000000000001246E-02
	/// </summary>
	/// <param name="value"></param>
	/// <param name="precision"></param>
	/// <returns></returns>
	inline static std::string ToScientific(const std::string& value, int precision) {

		try
		{
			std::string sResult;
			double dValue = std::stod(value);

			// step 1: rounding
			std::stringstream ss;
			ss << std::fixed << std::setprecision(precision) << dValue;

			sResult = ss.str();
			// step 2: move decimal point
			if (sResult.find('.') != sResult.npos)
			{
				std::vector<std::string> Splitted;
				uni_box::utils::split(sResult, Splitted, ".");
				std::string size_ = uni_box::utils::TtoStr(Splitted[1].size());

				//TODO：待确认，ABB 发个TM 若为1125.00 则发送为 1125E000 而不是 112500E-2
				// 判断小数位是否为零
				if (std::stoi(Splitted[1]) == 0)
				{
					sResult = uni_box::utils::PadLeft((Splitted[0]), 20, '0').append("E000");
					return sResult;
				}

				sResult = uni_box::utils::PadLeft((Splitted[0] + Splitted[1]), 20, '0');
				sResult += "E-";
				sResult += uni_box::utils::PadLeft(size_, 2, '0');

				// decimal part
			}
			else
			{
				// no decimals so we use the default "E000"
				sResult.assign(20, '0').append("E000");
			}
			return sResult;
		}
		catch (const std::exception& e)
		{
			logger_.Error(fmt::format("The error occurred in {0}, because:{1}", "ToScientific", e.what()));
			return value;
		}
	}


	/// <summary>
	/// 每个字段解码：统一返回string，手动根据指定类型进行转换
	/// </summary>
	/// <param name="value"></param>
	/// <param name="datatype"></param>
	/// <returns></returns>
	inline static  std::string ValueDecode(std::string value, std::string datatype)
	{
		try
		{
			if (datatype == "R")
			{
				return std::to_string(FromScientific(value));
			}
			else if (datatype == "I")
			{
				return std::to_string(static_cast<int>(FromScientific(value)));
			}
			else if (datatype == "U")
			{
				return std::to_string(static_cast<unsigned int>(FromScientific(value)));
			}
			else if (datatype == "B")
			{
				return (static_cast<unsigned int>(FromScientific(value)) > 0) ? "true" : "false";
			}
			else if (datatype == "T")
			{
				return uni_box::utils::trimCopy(value.substr(0, 20));
			}
			else if (datatype == "D")
			{
				return uni_box::utils::trimCopy(value.substr(0, 20));
			}
			else
			{
				throw std::invalid_argument("Invalid data type");
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Error in ValueDecode(), reason:{}", e.what()));
		}
	}

	/// <summary>
	/// 统一返回一个类型，根据data_type 转换实际类型
	/// </summary>
	/// <param name="value"></param>
	/// <param name="datatype"></param>
	/// <returns></returns>
	inline static std::any ValueDecodeAny(std::string value, std::string datatype)
	{
		renaissance::log::LOG_INFO("ValueDecodeAny Start.......");

		try
		{
			if (datatype == "R")
			{
				//logger_.Info(fmt::format("解析前:value:{0}, datatype:{1}", value, datatype));
				auto vaue = FromScientific(value);
				//logger_.Info(fmt::format("解析后:value:{0}, datatype:{1}", vaue, datatype));
				return vaue;
			}
			else if (datatype == "I")
			{
				//logger_.Info(fmt::format("解析前:value:{0}, datatype:{1}", value, datatype));
				auto vaue = static_cast<int>(FromScientific(value));
				//logger_.Info(fmt::format("解析后:value:{0}, datatype:{1}", vaue, datatype));
				return vaue;
			}
			else if (datatype == "U")
			{
				//logger_.Info(fmt::format("解析前:value:{0}, datatype:{1}", value, datatype));
				auto vaue = static_cast<unsigned int>(FromScientific(value));
				//logger_.Info(fmt::format("解析后:value:{0}, datatype:{1}", vaue, datatype));
				return vaue;
			}
			else if (datatype == "B")
			{
				//logger_.Info(fmt::format("解析前:value:{0}, datatype:{1}", value, datatype));
				auto vaue = (std::stoi(value) > 0) ? true : false;
				//logger_.Info(fmt::format("解析后:value:{0}, datatype:{1}", vaue, datatype));
				return vaue;
			}
			else if (datatype == "T")
			{
				//logger_.Info(fmt::format("解析前:value:{0}, datatype:{1}", value, datatype));
				auto vaue = uni_box::utils::trimCopy(value.substr(0, 20));
				//logger_.Info(fmt::format("解析后:value:{0}, datatype:{1}", vaue, datatype));
				return vaue;
			}
			else if (datatype == "D")
			{
				//logger_.Info(fmt::format("解析前:value:{0}, datatype:{1}", value, datatype));
				auto vaue = uni_box::utils::trimCopy(value.substr(0, 20));
				//logger_.Info(fmt::format("解析后:value:{0}, datatype:{1}", vaue, datatype));
				return vaue;
			}
			else
			{
				logger_.Error(fmt::format("Invalid data type:value:{0}, datatype:{1}", value, datatype));
				throw std::invalid_argument("Invalid data type");
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Error in ValueDecodeAny(), reason:{}", e.what()));
		}

		renaissance::log::LOG_INFO("ValueDecodeAny End.......");

	}
	/// <summary>
	/// Converts the input string to a double value
	/// 保留两位小数
	/// </summary>
	/// <param name="ValueString"></param>
	/// <returns></returns>
	inline static double FromScientific(std::string ValueString)
	{
		// Converts the input string to a double value
		// The input string contains the following parts:
		// ValuePart: An integer leftpadded with '0' to length = 20 characters (no + sign and - sign inside string)
		// Filler:    "E" characters
		// Exponent:  An integer leftappded with '0' to length = 3 characters (+ or - sign leftmost)

		// Get the valuepart of the string
		std::string ValuePart = ValueString.substr(0, 20);

		// Remove zeroes preceeding minus sign (if negative value) and convert to double
		if (ValuePart.find('-') != std::string::npos)
		{
			std::vector<std::string> ValuePartSplit;
			uni_box::utils::split(ValuePart, ValuePartSplit, "-");
			ValuePart = '-' + ValuePartSplit[1];
		}
		double Value = std::stod(ValuePart);

		// Get the exponent part of the string and convert to double
		double Exp = std::stod(ValueString.substr(21, 3));

		// Multiply/divide with exponent part (Math.Pow(10,Exp) does not give exact answer)
		if (Exp < 0)
			return Value / std::stod((uni_box::utils::PadRight("1", (int)(-1 * Exp + 1), '0')));
		else
			return Value * std::stod((uni_box::utils::PadRight("1", (int)(Exp + 1), '0')));
	}

	/// <summary>
	/// Helper method to determine if an itemName is
	/// valid or not. Only tests that first char is "D" or "X:模轧".</summary>
	/// <param name="itemName"></param>
	/// <returns></returns>
	inline static bool IsItemNameValid(const std::string& itemName)
	{
		if (itemName.empty())
		{
			return false;
		}

		char firstChar = std::toupper(itemName[0]);
		return (firstChar == 'D' || firstChar == 'X');
	}



	inline static void HandleTMUnremove(const shared_define::tm_message::TMInfo& tmInfo)
	{
		// Get the ProdReqResponse object
		auto res = DB::OracleDB::OracleDML::executeQuery(uni_box::utils::string_format("select ID,IN_STATE,,STATENAME,SUBSTATE from TB_PDI where COIL_ID = '%s'  order by UPDATE_TIME desc ", tmInfo.Item.c_str()));

		try
		{
			// check for conditions for unremove
			if (res.rs_.Next())
			{
				auto id_ = res.rs_.Get<shared_define::ID_TYPE>("ID");

				if (res.rs_.Get<std::string>("STATENAME") != shared_define::OrderStateTypes::OrderIsFinished &&
					res.rs_.Get<int>("SUBSTATE") != (int)shared_define::SubStatesEnum::IsRejected)
					return;
				else if (ActualResponseFlyw::FindOne(id_, shared_define::EquipNames::REJ_DATA, shared_define::PropNames::REJECT_LOCATION, 0) == nullptr)
					return;

				// Remove reject data
				ActualResponseFlyw::DeleteActualResponses(id_, ActualResponseFlyw::CacheEquipNameId()[shared_define::EquipNames::REJ_DATA], -1);
			}
			else
			{
				throw std::logic_error(uni_box::utils::string_format("The matId {%s} requested for unremove does not exist in TB_PDI", tmInfo.Item.c_str()));
			}
		}
		catch (const std::exception& e)
		{
			throw e;
		}
	}



	inline static std::string CombineEquipProp(const std::string& equipName, const std::string& propName)
	{
		return (equipName + "_" + propName);
	}



	/// <summary>
	/// 判断表TB_PDI中是否存在指定 matId 的记录，有则存储记录的ID，并返回true
	/// </summary>
	/// <param name="matId"></param>
	/// <returns></returns>
	static inline bool FindByMatId(const std::string& matId, shared_define::ID_TYPE& prodReqId)
	{
		try
		{
			auto sel_ = fmt::format("select ID from TB_PDI where COIL_ID='{0}'  ", matId);
			auto res = DB::OracleDB::OracleDML::executeQuery(sel_);
			if (res.rs_.Next())
			{
				prodReqId = res.rs_.Get< shared_define::ID_TYPE>("ID");
				return true;
			}
			else
			{
				return false;
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Error in FindByMatId to search matId:{0} in TB_PDI, reason:{1}", matId, e.what()));
		}

		return false;
	}
#pragma endregion

private:
	inline static renaissance::log::Logger& logger_ = renaissance::log::Logger::getInstance();
};


//renaissance::parser::XMLParser Common::par_;
//renaissance::parser::MsgCollectionType Common::RecvMessageCollectino;
//renaissance::parser::MsgCollectionType Common::SendMessageCollectino;

#endif