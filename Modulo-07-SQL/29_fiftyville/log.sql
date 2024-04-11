-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Mantenha um registro de todas as consultas SQL que você executar enquanto resolve o mistério.

--O Pato CS50 foi roubado! A cidade de Fiftyville convocou você para resolver o mistério do pato roubado. As autoridades acreditam que o ladrão roubou o pato e, logo depois, pegou um voo para fora da cidade com a ajuda de um cúmplice. Seu objetivo é identificar:

--Quem é o ladrão,
--Em que cidade o ladrão escapou e
--Quem é o cúmplice do ladrão que o ajudou a escapar.

--Tudo o que você sabe é que o roubo ocorreu em 28 de julho de 2020 e que aconteceu na Rua Chamberlin.
-----------------------------------------------------------------

-- para verificar se a queixa está registrada e obter informações sobre ela
SELECT * FROM crime_scene_reports WHERE street LIKE "%Chamberlin Street%" AND description LIKE "%CS50 DUCK%";

-- para obter informações sobre a entrevista com a polícia
SELECT * FROM interviews WHERE transcript LIKE "%courthouse%" AND day = 28 AND month = 7 AND year = 2020 ;

SELECT * FROM courthouse_security_logs WHERE activity = "exit" AND hour = 10 AND minute >= 15 AND minute <= 30 AND day = 28 AND month = 7 AND year = 2020 ;


-- Suspeitos: Patrick, Ernest, Amber, Danielle, Roger, Elizabeth, Russell e Evelyn
SELECT * FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute >= 15 AND minute <= 30 AND activity = "exit" ;

-- Suspeitos: Ernest, Elizabeth, Russell, Danielle
SELECT * FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ;

-- Apenas suspeitos restantes: Ernest, Russell
SELECT * FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60 ;

-- Apenas o suspeito restante é Ernest.
SELECT * FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = ( SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 ORDER BY hour, minute) ;

-------------------------------------

--Para qual cidade o ladrão vai?
SELECT city FROM airports WHERE id = ( SELECT destination_airport_id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 ORDER BY hour, minute LIMIT 1) ;

--Nome do ajudante
SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest" ) ;

--The THIEF is: Ernest
--The thief ESCAPED TO: London
--The ACCOMPLICE is: Berthold








