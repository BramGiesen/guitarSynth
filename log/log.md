# Guitar Synth Log

###### Blokschema:

<img src="images/BlokSchemaV2.jpg">

###### signal flow:
<img src="images/flowChart.jpg">


Voordat ik aan deze plugin ben begonnen heb ik eerst een kleinere plugin gemaakt
 <a href="https://bramgiesen.com/ringmodplugin.html">(hier te vinden)</a> om mij te verdiepen in JUCE en al wat zaken te testen zoals het implementeren van LFO's.

###### Filters:
Voor de filter implementatie heb ik gekozen voor een biquad filter, direct form II. Deze filter werkt met twee delaybuffers. Voor de buffers gebruik ik een aantal vectors. Ik ben begonnen met een mono implementatie, dus waarbij je voor ieder stereo-kanaal twee buffers moest aanmaken. Nadat ik dit werkend had ben ik gaan nadenken hoe ik dit efficiënter kon maken.

Toen kwam ik op het idee om 3d vectors te gebruiken. Ik heb 1 vector aangemaakt waarin 2 vectoren zitten voor de kanalen(stereo) deze vectoren bevatten ieder weer twee vectoren voor de delayBuffers.

```
channelBuffers[channel][delayBuffer][delay];

```

Ik had eerst een implementatie waarbij het geluid dubbel werd gefilterd, hierdoor werd het erg zacht, hierdoor moest ik het heel erg versterken, uiteindelijk heb ik ervoor gekozen om minder filters te gebruiken en nu klinkt het harder en ook een stuk beter. 

###### for loops:

Omdat er een behoorlijk aantal filters in een vocoder zitten, 30 stuks, heb ik mijn programma zo geschreven dat deze worden aangemaakt en ook binnen de process-functie heb ik veel for loops gebruikt om de code op deze manier flexibel en overzichtelijk te houden.

```
bandPassFilters = new Biquad*[60];


for (int i = 0; i < 60; i++){
    bandPassFilters[i]
    = new Biquad(1.0, filterFreqs[i % 15]
      / lastSampleRate, 40.0);
}

```

```
for (int filterIndex = 0; filterIndex < 15; filterIndex++){
             float filterSignal = bandPassFilters
             [filterIndex + 15]->process(channel, synthSample);
             addedfilterSignal = (filterSignal * envFollowValues[filterIndex]) + addedfilterSignal;
         }
```


###### Zerox:

Ik voor mijn zero crossing class het zerox~ object van Max als referentie genomen. Ik heb gekeken naar de werking van het object en naar de output. Hierna heb ik gekeken hoe ik dit zelf zou kunnen maken en ik heb nadat ik de code had gemaakt de output van mijn Zerox class vergeleken met het zerox~ object van Max om zo mijn output te verifiëren.

###### Envelope follower:

<img src="images/envelope_detection_fig2_11007.jpg">

Dit is het systeem dat heb gebruikt voor mijn envelope follower. Het artikel is <a href="https://www.dsprelated.com/showarticle/938.php">hier</a> te lezen. De absolute value bereken ik door de absolute waarde te pakken van het inkomende signaal over een x aantal samples. Als alle waarden bij elkaar zijn opgeteld deel het ik weer door x.
Dit gaat vervolgens door een one pole lowpass filter heen.

###### oscillatoren:
Naast het analyse deel en filtering heeft een vocoder ook een aantal oscillatoren. Als basis heb ik de classes uit blok csd2c gebruikt. Voor de noise oscillator heb ik de sinus formule vervangen met een random functie om op deze manier ruis te genereren. Op dit moment gebruik ik FM-synthese om een vollere klank te krijgen.  

###### Aubio:
Ik vond het lastig om aubio aan de praat te krijgen binnen Xcode. Uiteindelijk bleek dat ik het framework via een ander menu moest toevoegen.  

Hierna ging de rest relatief makkelijk. Ik moest wel de window en hopsize aanpassen om goede resultaten te halen.
In eerste instantie stond de window- en hopsize redelijk laag en hierdoor trackte aubio alleen de hoge noten redelijk, alle lagere frequenties niet. nadat ik de windowsize had veranderd naar 4096 en de hopsize naar 1024 werkt het goed.

Ik koppel aubio aan JUCE door de samples afkomstig uit de buffer van JUCE weg te schrijven naar een ringbuffer, deze geef ik doormiddel van een pointer door aan aubio.

###### Van aubio naar de synth:

Aubio pakte de frequenties redelijk goed maar er zaten wel pieken en dalen in de pitch in Hertz die aubio teruggaf.
hiernaast waren er ook nog andere kleinere fluctuaties alsmede dat de pitches die aubio terug geeft niet stemmingssysteem gebonden zijn dus passen zij ook niet allemaal in ons westers stemmingssysteem. Om dit op te lossen reken ik de frequenties van aubio eerst om naar de MIDI-nootwaarde waar de frequentie het dichst bij zit. Hierna geef ik die MIDI-nootwaarde door aan een mtof functie die het weer omzet naar de juiste frequentie.

Om de fluctuaties tegen te gaan schrijf ik de gedetecteerde pitches weg in een array en wordt er iedere 200 samples gekeken welke pitch er het meeste in de array voorkwam en deze wordt dan doorgeven aan de synth.

###### GUI:

Ik had in mijn oorspronkelijke GUI de parameters aangemaakt in for loops en in verschillende structs, hiermee word de GUI in verschillende vlakken onderverdeeld. Hoewel dit een mooier systeem was heb ik dit voor nu laten zitten in verband met de tijd. De GUI zelf stond al maar hij moest nog gekoppeld worden aan de processor class van JUCE. Omdat ik nog niet had uitgezocht hoe ik dit precies moest doen dacht ik dat het toch iets te veel tijd zou gaan kosten. Hierom heb ik gekozen om te gaan voor een vergelijkbare GUI die ik al in een eerder project had gebruikt omdat ik hierbij precies wist hoe ik het moest coderen.
