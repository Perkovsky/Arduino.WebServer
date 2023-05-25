<template>
    <div v-if="error">
        <v-snackbar
            v-model="error"
            color="error"
            :timeout="2000"
        >
            {{error}}

            <template v-slot:actions>
                <v-btn
                    color="dark"
                    variant="text"
                    @click="close"
                >
                Close
                </v-btn>
            </template>
        </v-snackbar>
    </div>
</template>

<script>
import { computed } from "vue"
import { useErrorStore } from '@/store'

export default {
  setup() {
    const errorStore = useErrorStore()
    let error = computed(() => errorStore.error)

    return {
      error,
      close() {
        errorStore.clear()
      },
    }
  },
}
</script>