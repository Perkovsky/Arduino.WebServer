import { createRouter, createWebHistory } from 'vue-router'
import { useAuthStore, useErrorStore } from '@/store'
import accountRoutes from './account.routes'
import Dashboard from '@/components/Dashboard.vue'

export const router = createRouter({
    history: createWebHistory(import.meta.env.BASE_URL),
    linkActiveClass: 'active',
    routes: [
        { path: '/', component: Dashboard },
        { ...accountRoutes },
        // catch all redirect to Dashboard page
        { path: '/:pathMatch(.*)*', redirect: '/' }
    ]
})

router.beforeEach(async (to) => {
    // clear error on route change
    const errorStore = useErrorStore()
    errorStore.clear()

    // redirect to login page if not logged in and trying to access a restricted page 
    const loginPage = '/login'
    const authRequired = to.path != loginPage
    const authStore = useAuthStore()

    if (authRequired && !authStore.isAuthorized) {
        authStore.returnUrl = to.fullPath
        return loginPage
    }
})