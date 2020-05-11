# ESPbutton_MQTT

Using the ESP-01 or ESP-01S combined with the PCA9536 IO expander, ESPbutton_MQTT provides 4 buttons with direct MQTT messaging.

MQTT messages are sent only on button state changes. You can switch from active high to active low buttons.
Each button is treated independently, for example if 1 button is already kept pressed (MQTT message already sent) and another one is pressed then only the new one is sent over MQTT.