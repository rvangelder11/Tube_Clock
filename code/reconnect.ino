void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    //P.print("Attempting MQTT connection");
    // Attempt to connect
    if (client.connect("Lichtkrant")) {
      Serial.println("connected");
      //P.print("   connected");
      // Subscribe
      client.subscribe("Lichtkrant/verwachting");
      client.subscribe("Lichtkrant/bui_minuten");
      client.subscribe("Lichtkrant/LaatsteNieuws");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      //P.print("   MQTT connection failed");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
