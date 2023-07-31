void NL_tijd_tekst(int minuut, int uur, char tekst[50]) {
  char *getal[15] = {"twaalf", "één", "twee", "drie", "vier", "vijf", "zes", "zeven", "acht", "negen", "tien", "elf", "twaalf", "dertien", "veertien"};
  if (uur > 12) uur = uur - 12; // we tellen tot twaalf en gaan dan weer naar 1
  if (uur == 12 and minuut > 15) uur = 0; // na 12:15 verwijzen we naar 1 uur. omdat er dan altijd 1 bij wordt opgeteld, moet hier nul staan
  if (minuut == 0) sprintf(tijd_tekst, "%s uur", getal[uur]);
  if (minuut > 0 and minuut < 15) sprintf(tijd_tekst, "%s over %s", getal[minuut], getal[uur]);
  if (minuut == 15) sprintf(tijd_tekst, "kwart over %s", getal[uur]);
  if (minuut > 15 and minuut < 30) sprintf(tijd_tekst, "%s voor half %s", getal[30 - minuut], getal[uur + 1]);
  if (minuut == 30) sprintf(tijd_tekst, "half %s", getal[uur + 1]);
  if (minuut > 30 and minuut < 45) sprintf(tijd_tekst, "%s over half %s", getal[minuut - 30], getal[uur + 1]);
  if (minuut == 45) sprintf(tijd_tekst, "kwart voor %s", getal[uur + 1]);
  if (minuut > 45 and minuut <= 59) sprintf(tijd_tekst, "%s voor %s", getal[60 - minuut], getal[uur + 1]);
  utf8AsciiString(tekst); // zet diacryten om van UTF8 naar exteded Ascii
}
