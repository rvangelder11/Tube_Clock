void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  for (int i = 0; i < length; i++) {
    messageTemp[i] = (char)message[i];
  }
  messageTemp[length] = '\0'; // make it a null terminated string
  utf8AsciiString(messageTemp);
  Serial.println(messageTemp);
  P.displayClear();
  P.displayScroll(messageTemp, PA_LEFT, PA_SCROLL_LEFT, 50);
  P.displayAnimate();
  strcpy(tijd_tekst_oud,""); // to make sure a time is printed after amessage has been displayed
}
