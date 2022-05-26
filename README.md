# DraughtsS

Cerinta: Sa se implementeze un server care sa ofere posibilitatea unor perechi de clienti 
sa joace diverse variatii de "draughts" (dame) si sa mentina clasamente diverse pentru fiecare tip de joc.

Resurse suplimentare: https://en.wikipedia.org/wiki/Draughts

Pentru a rula proiectul: make s, make c

Proiectul a fost realizat in cadrul disciplinei "Retele de calculatoare" si simuleaza jocul Draughts (Checkers), folosind o aplicatie de tip server/client. Serverul are responsabilitatea de a asigna culoarea fiecarui jucator (alb sau negru) si de a asigura buna desfasurare a jocului. Serverul valideaza mutarile jucatorilor, tine scorul si ofera posibilitatea jucatorilor de a alege ce tip de joc vor sa joace: International (clasic) sau Canadian. Clientul este responsabil de a afisa tabla de joc si de a trimite catre server o mutare pentru a fi validata si ulterior actualizata in tabla.
