import { Layout } from '@/layouts'
import Login from '@/components/Login.vue'

export default {
    path: '/',
    component: Layout,
    children: [
        { path: '', redirect: 'login' },
        { path: 'login', component: Login },
    ]
};
