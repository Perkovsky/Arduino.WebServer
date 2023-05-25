import { defineStore } from 'pinia'

export const useErrorStore = defineStore({
    id: 'error',
    state: () => ({
        error: null
    }),
    actions: {
        send(message) {
            this.error = message;
        },
        clear() {
            this.error = null;
        }
    }
})
