import createPersistedState from 'vuex-persistedstate'

export default ({ store }) => {
  createPersistedState({
    storage: {
      getItem: function(key) {
        return localStorage.getItem(key)
      },
      // Please see https://github.com/js-cookie/js-cookie#json, on how to handle JSON.
      setItem: function(key, value) {
        localStorage.setItem(key, value)
      },
      removeItem: function(key) {
        localStorage.removeItem(key)
      }
    }
  })(store)
}
