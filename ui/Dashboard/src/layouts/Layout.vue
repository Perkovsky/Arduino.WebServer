<template>
    <v-main>
        <router-view />
    </v-main>
</template>

<script setup>
import { useAuthStore } from '@/store'
import { router } from '@/router'

// redirect Dashboard if already logged in
const authStore = useAuthStore()
if (authStore.isAuthorized) {
    router.push('/')
}
</script>