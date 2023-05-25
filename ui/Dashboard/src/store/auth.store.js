import { defineStore } from 'pinia'
import { router } from '@/router'
import { useErrorStore } from '@/store'

const IS_AUTHORIZED_KEY_NAME = 'isAuthorized'

export const useAuthStore = defineStore({
    id: 'auth',
    state: () => ({
        // initialize state from local storage to enable user to stay logged in
        isAuthorized: localStorage.getItem(IS_AUTHORIZED_KEY_NAME),
        returnUrl: null
    }),
    actions: {
        login(username, password) {
            try {
                const isAuthorized = username === import.meta.env.VITE_USERNAME && password === import.meta.env.VITE_PASSWORD
                if (!isAuthorized) {
                    this.isAuthorized = null
                    localStorage.removeItem(IS_AUTHORIZED_KEY_NAME)
                    const errorStore = useErrorStore()
                    errorStore.send('Invalid username or password')
                    return
                }
                
                this.isAuthorized = true
                localStorage.setItem(IS_AUTHORIZED_KEY_NAME, this.isAuthorized)
                router.push(this.returnUrl || '/')
            } catch (error) {
                const errorStore = useErrorStore()
                errorStore.send(error)
            }
        },
        logout() {
            this.isAuthorized = null
            localStorage.removeItem(IS_AUTHORIZED_KEY_NAME)
            router.push('/login')
        }
    }
})
