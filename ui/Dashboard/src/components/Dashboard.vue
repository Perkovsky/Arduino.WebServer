<template>
  <v-container class="fill-height">
    <v-responsive class="d-flex align-top text-center fill-height">
      <v-img height="100" src="@/assets/logo.svg" />
      <h class="text-h4 font-weight-bold">Welcome to ESP32 Dashboard</h>
      <div class="py-14" />

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
</template>

<script>
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
    },
    methods: {
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
          // .then(response => {
          //   console.log(response.data)
          //   // do nothing
          // })
          .catch(error => {
            console.log(error)
          })
      },
      toggleLedRed() {
        this.$http.post('/toggle-led-red', { value: Number(!!this.ledRed) })
          // .then(() => {
          //   //this.getTemperature()
          //   // do nothing
          // })
          .catch(error => {
            console.log(error)
          })
      }
    }
  }
</script>
