<template>
  <v-app>
    <v-main>
      <router-view />
    </v-main>
    <Error />
  </v-app>
</template>

<script setup>
import Error from '@/components/Error.vue'
</script>