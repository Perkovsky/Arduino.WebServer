<template>
    <div class="d-flex align-center justify-center" style="height: 90vh">
        <v-sheet width="400" class="mx-auto">
            <v-img height="100" src="@/assets/logo.svg" />
            <v-form fast-fail @submit.prevent="login">
                <v-text-field 
                    v-model="username"
                    variant="underlined"
                    clearable
                    label="Username" />
                <v-text-field
                    v-model="password"
                    variant="underlined"
                    clearable
                    label="Password"
                    type="password" />
                <v-btn color="primary" block class="mt-2" @click="login">Sign in</v-btn>
            </v-form>
        </v-sheet>
    </div>
</template>

<script>
import { useAuthStore } from '@/store'

export default {
    data() {
        return {
            username: '',
            password: '',
        }
    },
    methods: {
        login() {
            const authStore = useAuthStore()
            authStore.login(this.username, this.password)
        },
    },
}
</script>