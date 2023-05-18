import App from './App.vue'
import { createApp } from 'vue'
import { registerPlugins } from '@/plugins'
import axios from 'axios'

const app = createApp(App)

// Set up axios
axios.defaults.baseURL = import.meta.env.VITE_API_URL
axios.defaults.headers.common['Accept'] = 'application/json'
axios.defaults.headers.common['api_key'] =  import.meta.env.VITE_API_KEY

app.config.globalProperties.$http = axios

registerPlugins(app)

app.mount('#app')
