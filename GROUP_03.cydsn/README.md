05.04.21
Il TopDesign è stato fatto, in caso di perplessità o chiarimenti non presenti in questo log, scrivere a oswaldo.parra@mail.polimi.it o oswaldo.w.parra@gmail.com.
gli elementi sono stati collocati nello schematico e mappati nei pin fisici dello PSoC.
E' stato aggiunto il time in modo da mandare il segnale di timeout tramite un'interrupt di priorità più alta rispetto a quello inerente alla UART (E.G. ad ogni interrupt incrementa un conteggio e confronta con il numero che non deìvessere superato, if raggiunto stacca tutto), il timer ha un TC di 1 secondo quindi si può impostare l'interrupt in modo da far contare i TC al timer e bloccare tutto quando questo conteggio raggiunge il numero immesso dal terminale come descritto nelle specifiche di progetto, il timer ha un segnale di enable per inizializzare il conteggio solo quando necessario, nel programma possiamo dare un segnale di enable tramite la porta a cui è collegato questo segnale.
Oswaldo


Tolta l'attivazione hardware per il timer, meglio utilizzare "void Timeout_Interrupt_Enable(void);" per attivarlo quando bisogna iniziare a contare e "void Timeout_Interrupt_Disable(void);" per smettere
