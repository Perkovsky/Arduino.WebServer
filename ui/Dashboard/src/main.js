import App from './App.vue'
import { createApp } from 'vue'
import { registerPlugins } from '@/plugins'
import axios from 'axios'

const app = createApp(App)

// Set up axios
//axios.defaults.baseURL = 'http://localhost:5282'
axios.defaults.headers.common['Accept'] = 'application/json'

app.config.globalProperties.$http = axios

registerPlugins(app)

app.mount('#app')
