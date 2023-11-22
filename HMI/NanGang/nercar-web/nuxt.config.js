const pkg = require('./package')
module.exports = {
  mode: 'universal',
  // mode: 'spa',
  /*
  ** Headers of the page
  */
  head: {
    title: 'nercar-web',
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      { hid: 'description', name: 'description', content: pkg.description }
    ],
    link: [{ rel: 'icon', href: 'iplat.ico' }]
  },

  /*
  ** Customize the progress-bar color
  */
  // loading: { color: '#fff' },
  loading: false,

  /*
  ** Global CSS
  */
  css: [
    'element-ui/lib/theme-chalk/index.css',
    '@/assets/icon/iconfont.css',
    '@/assets/css/reset.css'
  ],

  /*
  ** Plugins to load before mounting the App
  */
  plugins: [
    '@/plugins/element-ui',
    '@/plugins/directive',
    '@/plugins/api',
    '@/plugins/filters',
    '@/plugins/i18n',
    { src: '~/plugins/persistedstate.js', ssr: false },
    { src: '~/plugins/vue-echarts.js', ssr: false }
  ],

  /*
  ** Nuxt.js modules
  */
  modules: [
    // Doc: https://github.com/nuxt-community/axios-module#usage
    '@nuxtjs/axios'
  ],
  server: {
    // 前端端口号
    port: 8001 || process.env.PORT,
    host: '0.0.0.0' || process.env.BASE_URL
  },
  /*
  ** Axios module configuration
  */
  env: {
    baseUrl: process.env.BASE_URL
  },
  axios: {
    baseURL: 'http://localhost:8088/', //设置统一URL,关闭代理时使用.
    timeout: 60000,
    retry: { retries: 3 },
    proxy: true // 表示开启代理
  },
  proxy: {
    '/api': {
      //匹配代理对象
      target: 'http://localhost:8088/', // 目标接口域名
      pathRewrite: { '^/api': '' }, // 匹配 /api 替换成 /
      changeOrigin: true, // 表示是否跨域
      logLevel: 'debug'
    }
  },
  /*
  ** Build configuration
  */
  build: {
    /*
    ** You can extend webpack config here
    */
    uglify: {
      uglifyOptions: {
        compress: true
      },
      cache: true
    },
    extend(config, ctx) {
      // Run ESLint on save
      if (ctx.isDev && ctx.isClient) {
        config.module.rules.push({
          enforce: 'pre',
          test: /\.(js|vue)$/,
          loader: 'eslint-loader',
          exclude: /(node_modules)/
        })
      }
    }
  }
}
