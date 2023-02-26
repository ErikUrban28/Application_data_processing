<h1> Apikácia na spracovanie údajov zo Sčítania obyvateľov domov a bytov z roku</h1>

<h2>Používateľská príručka</h2> 
Po spustení programu užívateľ krátku dobu čaká na načítanie dát o čom je aj informovaný.
Následne sa na konzole objaví zoznam operácií, z ktorých si užívateľ môže vyberať.
Program vyzýva užívateľa väčšinou na číselný input pre voľbu žiadanej operácie. Každá operácia musí byť potvrdená ENTER-om!

**Bodové vyhľadávanie** si najprv vyžiada typ územnej jednotky  a následne žiada názov určitej územnej jednotky v presnom tvare, ktorým je oficiálny názov územnej jednotky. Názov musí byť platný pre daný typ územnej jednotky. Okresy majú slovo 'Okres' pred svojim oficiálnym názvom. Kraje majú zas slovo kraj za svojim oficiálnym názvom. Takže je rozdiel napr. medzi 'Žilina' a 'Okres Žilina'  a 'Žilinský kraj'. Prvé určuje obec, ďalšie okres a posledné kraj. Duplicity majú navyše pridané k svojmu názvu aj priamu nadradenú jednotku. Takže ak máme napr. obec Píla, ktorá má duplicitu tak musí užívateľ napísať bez apostrofov a medzerami
'Píla – Lučenec' , kde Píla je názov obce a Lučenec je názov vyššej územnej jednotky, čiže názov okresu.

**Pri filtrácii** si užívateľ vyberá najprv či chce alebo nechce použiť filtre. Ak nechce, tak sa vypíšu všetky územne jednotky zoradené podľa ich kódu. Vypíšu sa ich názvy, typ a názvy a typy nadriadených jednotiek danej územnej jednotky. Ak chce užívateľ používať filtre, je vyzvaný k tomu, aby si vybral, či chce AND alebo OR logickú operáciu. Pri AND to znamená, že územná jednotka musí spĺňať všetky filtre, aby bola vložená do vyfiltrovanej tabuľky. Pri OR stačí, ak spĺňa aspoň jeden filter. Po vybratí logickej operácie si môže užívateľ vybrať zo zoznamu filtrov, ktoré budú aplikované. 
Potom už stačí stlačiť a potvrdiť tlačidlo 7, pre 'Uz nevyberat'. Následne sa vypíšu všetky územné jednotky, ktoré vyhovujú filtrom, podľa vybranej logickej operácie.

**Pri triedení** je užívateľ vyzvaný vybrať si najprv zo spoločných filtrov a potom ďalej z filtrov, s kritériom podľa ktorých sa bude triediť. Po vyfiltrovaní je ešte užívateľ vyzvaný k tomu, či chce utriediť tabuľku vzostupne alebo zostupne. Potom sú už územné jednotky vypísané na konzolu podľa vybraných parametrov.
Posledná operácia je ukončenie aplikácie, ktorú keď si zvoli užívateľ ukončí aplikáciu.
