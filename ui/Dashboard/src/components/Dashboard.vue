<template>
 <v-layout>
      <v-app-bar
        color="primary"
        density="compact"
      >
        <v-app-bar-title>ESP32 Dashboard</v-app-bar-title>

        <template v-slot:append>
          <v-btn icon="mdi-logout-variant" @click="logout"></v-btn>
        </template>
      </v-app-bar>

      <v-main>
        <v-container class="fill-height">
          <v-responsive class="d-flex align-top text-center fill-height">
            <div class="py-2" />

            <v-row class="d-flex align-top justify-center">
              <v-col cols="auto">
                <div>
                  <v-icon
                    size="large"
                    color="blue"
                    icon="mdi-water"
                  />Humidity: <b>{{ humidity }}</b>%
                </div>
              </v-col>
              <v-col cols="auto">
                <div>
                  <v-icon
                    size="large"
                    color="red"
                    icon="mdi-thermometer"
                  />Temperature: <b>{{ temperature }}</b>°C
                </div>
              </v-col>
            </v-row>

            <v-row class="d-flex align-top justify-center">
              <v-col cols="auto">
                <v-switch
                    v-model="ledBlue"
                    label="LED Blue"
                    color="blue"
                    hide-details
                    @change="toggleLedBlue"
                />
              </v-col>
              <v-col cols="auto">
                <v-switch
                    v-model="ledRed"
                    label="LED Red"
                    color="red"
                    hide-details
                    @change="toggleLedRed"
                />
              </v-col>
            </v-row>
          </v-responsive>
        </v-container>
      </v-main>
    </v-layout>
</template>

<script>
import { useAuthStore } from '@/store'

export default {
  data () {
    return {
      temperature: '--',
      humidity: '--',
      ledBlue: false,
      ledRed: false
    }
  },
  mounted() {
    this.getLedBlueStatus()
    this.getLedRedStatus()
    this.getTemperature()
    this.getHumidity()

    this.$options.sockets.onmessage = (message) => {
      const data = JSON.parse(message.data)
      this.temperature = data.temperature
      this.humidity = data.humidity
      this.ledBlue = data.ledBlueStatus
      this.ledRed = data.ledRedStatus
    }
  },
  methods: {
    logout() {
      const authStore = useAuthStore()
      authStore.logout()
    },
    getTemperature() {
      this.$http.get('/temperature')
        .then(response => {
          this.temperature = response.data
        })
        .catch(error => {
          console.log(error)
        })
    },
    getHumidity() {
      this.$http.get('/humidity')
        .then(response => {
          this.humidity = response.data
        })
        .catch(error => {
          console.log(error)
        })
    },
    getLedBlueStatus() {
      this.$http.get('/led-blue-status')
        .then(response => {
          this.ledBlue = response.data
        })
        .catch(error => {
          console.log(error)
        })
    },
    getLedRedStatus() {
      this.$http.get('/led-red-status')
        .then(response => {
          this.ledRed = response.data
        })
        .catch(error => {
          console.log(error)
        })
    },
    toggleLedBlue() {
      this.$http.post('/toggle-led-blue', { value: Number(!!this.ledBlue) })
        .catch(error => {
          console.log(error)
        })
    },
    toggleLedRed() {
      this.$http.post('/toggle-led-red', { value: Number(!!this.ledRed) })
        .catch(error => {
          console.log(error)
        })
    }
  }
}
</script>
