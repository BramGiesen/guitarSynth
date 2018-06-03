# Guitar Synth Log

###### GUI:

Parameters aangemaakt in for loops en in verschillende structs, hiermee word de GUI in verschillende vlakken onderverdeeld.

###### filters:

Omdat er een behoorlijk aantal filters in een vocoder zitten heb ik mijn programma zo geschreven dat deze worden aangemaakt en worden "afgespeeld" door middel van for loops.

Nadat ik de filter werkend had heb ik deze in 3d vectors
gestopt: channelBuffers[channel][delayBuffer[delay].
Hierbij worden er dus per kanaal twee buffer lijsten in de vector gezet. Ik werk met Biquad direct form II. deze maakt gebruik van twee delaybuffers.

###### envelope follower:

<img src="images/envelope_detection_fig2_11007.jpg">
Dit is het systeem dat heb gebruikt voor mijn envelope follower. De absolute value bereken ik door de absolute waarde te pakken van het inkomende signaal over een x aantal samples. Als alle waarden bij elkaar zijn opgeteld deel het ik weer door x.
Dit gaat vervolgens door een one pole lowpass filter heen.
