SELECT * FROM magazin;
SELECT * FROM stoc;
SELECT * FROM produs;
SELECT * FROM producator;
SELECT * FROM categorie;


/*Enun? ?i rezolvare (folosind schemele de mai sus) care s? implice utilizarea operatorului
DIVISION din algebra rela?ional? (oricare din cele 4 metode).*/

/*Selecteaza toate magazinele care au cel putin aceiasi producatori ca si produsele care sunt in stoc ale magazinului 3.
Va afisa 1, 2 si 4 deoarece 3 ii are drept producatori pentru magazinele din stoc pe 1, iar toate celelalte magazine il au ca producator pe 1
Daca magazinul 1 nu mai avea pe stoc produsul cu id-ul 1, magazinul 1 nu mai era afisat
Am folosit ultima metoda, pentru a se vedea clar ca daca scadem din toti producatorii lui 3(adica 1) pe ceilalti, ramane multimea vida*/
SELECT DISTINCT s2.cod_magazin
FROM stoc s2
WHERE NOT EXISTS 
(SELECT cod_producator 
FROM stoc s
JOIN produs p ON (p.id_produs = s.cod_produs)
WHERE cod_magazin = 3
MINUS 
SELECT cod_producator 
FROM stoc s
JOIN produs p ON (p.id_produs = s.cod_produs)
WHERE s.cod_magazin = s2.cod_magazin)       --sincronizare pe magazin
AND s2.cod_magazin <> 3;




/*S? se ob?in? magazinul care are în stock cea mai ieftin? tablet? Nexus 7. (7,5p)*/
SELECT id_magazin, denumire
FROM magazin m
JOIN stoc s ON(m.id_magazin = s.cod_magazin)
WHERE s.cod_produs = (SELECT id_produs                      --vedem cine are tablete nexus 7
                      FROM produs
                      WHERE lower(denumire) = 'nexus 7')
AND s.pret = (SELECT MIN(pret)                              --vedem care e cel mai mic pret al tabletelor nexus 7 de pe stoc
              FROM stoc
              WHERE cod_produs = (SELECT id_produs
                                  FROM produs
                                  WHERE lower(denumire) = 'nexus 7'));



/*S? se creeze tabelul client_pnu(id, nume, data_nastere, email) cu informa?ii generale despre
clien?i (unde sufixul de forma _pnu, 'p' este ini?iala prenumelui, iar 'nu' sunt primele 2 litere
ale numelui de familie). Ad?uga?i constrângerea de cheie primar? ?i o alt? constrângere la
alegere. Insera?i înregistr?ri cu date introduse de la tastatur?.*/
CREATE TABLE client_lco
                (
                id number(4) PRIMARY KEY,               --id-ul e cheie primara
                nume VARCHAR2(20) NOT NULL,             --nu putem pune valori nule la nume
                data_nastere date,
                email VARCHAR2(20) UNIQUE               --email-ul trebuie sa fie unic
                );
                
SELECT * FROM client_lco;

INSERT INTO client_lco (id, nume, data_nastere, email)
VALUES (&p_id, '&p_nume',TO_DATE('&p_data','DD/MM/YYYY'),'&p_email');

INSERT INTO client_lco (id, nume, email)
VALUES (&p_id, '&p_nume','&p_email');

COMMIT;

/*4. S? se afi?eze denumirea categoriei ?i denumirea produselor pentru care este cunoscut?
firma care asigur? service. (5p)*/

SELECT c.denumire, p.denumire
FROM categorie c
JOIN produs p ON (c.id_categorie = p.cod_categorie)
JOIN producator prod ON (prod.id_producator = p.cod_producator)
WHERE service IS NOT NULL;



