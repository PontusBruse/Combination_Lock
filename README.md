# Arduino Passcode System

Detta projekt implementerar ett passcodesystem för Arduino där användaren kan låsa upp och låsa systemet med en 4-knappars passkod. Det finns även ett programmeringsläge för att ändra passkoden genom att trycka på en särskild programmeringsknapp.

## Funktioner

- **Passcode Locking**: Systemet är initialt låst. För att låsa upp det behöver användaren trycka på knappar i rätt sekvens.
- **Programmeringsläge**: Genom att trycka på en särskild programmeringsknapp kan användaren ändra passkoden.
- **LED-indikatorer**: Två LED-lampor (röd och grön) används för att indikera systemets status:
  - **Röd LED**: Indikerar att systemet är låst.
  - **Grön LED**: Indikerar att systemet är upplåst.

## Komponenter

- 1x Arduino (t.ex. Arduino Uno)
- 4x tryckknappar (BTN_1, BTN_2, BTN_3, BTN_4)
- 1x programmeringsknapp (PROG_BTN)
- 2x LED (grön och röd)
- Motstånd för knappar och LED:ar

## Anslutningar

- **BTN_1 (Pin 5)**: Knappar för passkoden
- **BTN_2 (Pin 4)**: Knappar för passkoden
- **BTN_3 (Pin 3)**: Knappar för passkoden
- **BTN_4 (Pin 2)**: Knappar för passkoden
- **PROG_BTN (Pin 6)**: Programmeringsknappen för att ändra passkoden
- **GREEN_LED (Pin 12)**: Indikator för upplåst läge
- **RED_LED (Pin 11)**: Indikator för låst läge

## Hur det fungerar

1. **Systemet startar i låst läge**: Den röda LED-lampan är tänd och den gröna LED-lampan är släckt.
2. **Användaren trycker på knapparna i rätt sekvens**: Om användaren trycker på knapparna i rätt sekvens (standardpasskod: `BTN_4, BTN_2, BTN_1, BTN_4`), kommer den gröna LED-lampan att tändas och systemet upplåses.
3. **Programmeringsläge**: Genom att trycka på programmeringsknappen (`PROG_BTN`) kan användaren byta passkod. Under programmeringsläget blinkar båda LED-lamporna (röd och grön). När programmeringen är klar, sparas den nya passkoden och systemet återgår till låst läge.
4. **Passkodändring**: Användaren kan trycka på knapparna för att sätta den nya passkoden under programmeringsläge.

## Installationsinstruktioner

1. **Ladda ner och installera Arduino IDE**: Om du inte redan har Arduino IDE installerat, kan du hämta det från [Arduino's officiella webbplats](https://www.arduino.cc/en/software).
2. **Anslut din Arduino**: Anslut din Arduino till din dator via USB.
3. **Ladda upp koden**:
   - Öppna Arduino IDE och skapa ett nytt projekt.
   - Klistra in koden ovan i din sketch.
   - Välj rätt Arduino-modell och COM-port i IDE:n.
   - Klicka på "Upload" för att ladda upp koden till din Arduino.
4. **Anslut hårdvaran**: Följ anslutningarna ovan för att koppla knapparna och LED-lamporna till din Arduino.
5. **Testa systemet**: När koden är uppladdad och hårdvaran är korrekt ansluten, kan du testa systemet genom att trycka på knapparna i rätt sekvens för att låsa upp systemet.

## Användning

- **Låsa upp systemet**: Tryck på knapparna i den korrekta passkoden-sekvensen för att låsa upp systemet (standardpasskod är `BTN_4, BTN_2, BTN_1, BTN_4`).
- **Ändra passkod**: Gå in i programmeringsläge genom att trycka på programmeringsknappen (`PROG_BTN`), och ange den nya passkoden genom att trycka på knapparna i den nya sekvensen.

## Förbättringar

- Du kan ändra passkoden i koden genom att justera värdena i `passcode[]` arrayen.
- Programmet kan utökas med fler funktioner, som att lägga till en återställning av passkoden eller skydda programmeringsläget med en extra säkerhet.

### Utvecklare  
**Pontus Brusewitz**