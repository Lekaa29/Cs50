-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28; --Found description
SELECT * FROM interviews WHERE transcript LIKE "%bakery%"; --Got the interviews
SELECT * FROM people JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10; --names of suspects licence plates
SELECT * FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location LIKE "%Leggett%"; --names of suspects using exact atm
SELECT * FROM people JOIN phone_calls ON phone_calls.caller = people.phone_number WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60; --names of callers at suspected time
SELECT * FROM airports WHERE city LIKE "%Fiftyville%"; --got the id of origin airport
SELECT * FROM flights WHERE origin_airport_id = 8 AND day = 29 AND month = 7 AND year = 2021; --found earliest next day flight
SELECT passport_number FROM passengers WHERE flight_id = 36; --Found only one reaccuring person which is Bruce
SELECT name FROM people WHERE phone_number = "(375) 555-8161"; --Found the receiver of bruces call
SELECT full_name FROM airports WHERE id = 4; --found destination airport from ealier information of earliest next day flight