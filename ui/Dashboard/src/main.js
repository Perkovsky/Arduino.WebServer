import App from './App.vue'
import { createApp } from 'vue'
import { registerPlugins } from '@/plugins'
import axios from 'axios'
import VueNativeSock from "vue-native-websocket-vue3"
import { createPinia } from 'pinia'

const app = createApp(App)

// Set up axios
axios.defaults.baseURL = `http://${import.meta.env.VITE_API_URL}`
axios.defaults.headers.common['Accept'] = 'application/json'
axios.defaults.headers.common['api_key'] =  import.meta.env.VITE_API_KEY
app.config.globalProperties.$http = axios

// Set up WebSocket
app.use(VueNativeSock, `ws://${import.meta.env.VITE_API_URL}/ws`,  {
    format: 'json',
    reconnection: true,
    reconnectionAttempts: 5,
    reconnectionDelay: 3000,
})

registerPlugins(app)

// Pinia DevTools Bug: https://github.com/vuejs/devtools/issues/1839
//
//app.mount('#app')
app.use(createPinia()).mount('#app');
