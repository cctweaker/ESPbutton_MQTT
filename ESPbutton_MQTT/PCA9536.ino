void check_PCA()
{
    Wire.beginTransmission(PCA_ADDR);
    if (Wire.endTransmission() != 0)
    {
        // we have no PCA9536 on the bus
        ESP.restart();
    }
}

void read_PCA()
{
    Wire.beginTransmission(PCA_ADDR);
    Wire.write(INP_REG);
    if (Wire.endTransmission() == 0)
    {
        Wire.requestFrom(PCA_ADDR, 1);
        if (Wire.available())
            butoane = Wire.read();

        if (butoane != butoane_last)
        {
            char tx[128];

            bat = (float)ESP.getVcc() / FACTOR;
            sprintf(tx, "{\"t\":\"%s\",\"n\":\"%s\",\"b\":{1:%d,2:%d,3:%d,4:%d},\"bat\":%.2f}", TIP, NAME, bitRead(butoane, 0), bitRead(butoane, 1), bitRead(butoane, 2), bitRead(butoane, 3), bat);
            butoane_last = butoane;

            client.publish(MQTT_PUB_TOPIC, tx, false, 0);
        }
    }
    else
    {
        while (Wire.available())
            Wire.read();
    }
}