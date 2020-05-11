void check_PCA()
{
    Wire.beginTransmission(PCA_ADDR);

    if (Wire.endTransmission() == 0)
    {
        // PCA 9536 found!
        PCA = true;
        return;
    }

    PCA = false;
}

void read_PCA()
{
    Wire.beginTransmission(PCA_ADDR);
    Wire.write(INP_REG);
    if (Wire.endTransmission() == 0)
    {
        Wire.requestFrom(PCA_ADDR, 1);
        if (Wire.available())
            butoane = Wire.read() & 0x0F;

        if (butoane != butoane_last)
        {
            uint8_t ab = butoane & butoane_last;
            uint8_t xb = butoane ^ ab;

            butoane_last = butoane;

            if (xb > 0)
            {
                char tx[128];

                bat = ESP.getVcc() / FACTOR;

                sprintf(tx, "{\"t\":\"%s\",\"i\":\"%x\",\"b\":{1:%d,2:%d,3:%d,4:%d},\"bat\":%.2f}", TIP, ESP.getChipId(), bitRead(xb, 0), bitRead(xb, 1), bitRead(xb, 2), bitRead(xb, 3), bat);

                client.publish(MQTT_PUB_TOPIC, tx, false, 0);
            }
        }
    }
    else
    {
        while (Wire.available())
            Wire.read();
    }
}