# Mobateli

<h1> Introduction </h1>
<p> Ce document reprend les informations nécessaires à l'utilisation du dispositif de monitoring de batteries 
conçu à Kinshasa par l'ULB en collaboration avec la CAMESKIN dans le cadre du projet CODEPO 2021-2022. </p>
<p> Le dispositif a été développé de manière à être relativement simple d'utilisation à l'aide de 
l'écran LCD et des 4 différents boutons présents juste en dessous. </p>

<h1> Objectifs du dispositif </h1>
Le dispositif fournit 2 types de messages de monitoring: des alertes et des bilans journaliers :
<ul>
<li> ALERTES &#x2192; Les alertes ne se déclenchent qu'en cas de dysfonctionnement des batteries 
ou des panneaux solaires. Lorsque le dispositif détecte le problème, 
il envoie un message MQTT au Broker Thingstream. 
Ce dernier envoie ensuite un mail aux personnes de référence 
(voir la section "Thingstream" pour savoir en quoi consiste le broker thingstream et 
comment définir les personnes de référence). Chaque mail coûte 0,001\$ et doit être payé 
via la plateforme Thingstream. </li>
<li> BILANS JOURNALIERS &#x2192; Les bilans journaliers sont les données récoltées par le 
dispositif au cours de la journée. Ils sont envoyés chaque jour au Broker Thingstream qui 
les stocke en attendant que quelqu'un les récupère via les codes Python (voir la section "Codes Python"). </li>
