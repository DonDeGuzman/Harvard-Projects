-- Keep a log of any SQL inquiries you execute as you address the secret.
-- Checking the portrayal of the wrongdoing occurred at the given area and time.
SELECT
  description
FROM
  crime_scene_reports
WHERE
  year = 2021
  AND month = 7
  AND day = 28
  AND street = 'Humphrey Street';
-- Two episodes happened that day. Only one is connected with robbery. Other is connected with littering.
-- The observers could be the associate. In this way, observing the names of the observers from the meetings table. Additionally, really looking at their meetings' records.
SELECT
  name,
  transcript
FROM
  interviews
WHERE
  year = 2021
  AND month = 7
  AND day = 28;
-- Found two records with the name-Eugene, so checking the number of Eugenes are available in 'individuals' table.
SELECT
  name
FROM
  people
WHERE
  name = 'Eugene';
-- Figured out that there is just a single Eugene. Thus, continuing appropriately.
-- Findling the names of the 3 observers from the rundown of names of individuals who gave interviews on July 28, 2021. Wrongdoing report said that the observers referenced "bread kitchen" in their records. Additionally, requesting the outcomes in order by the names of witnesses.
SELECT
  name,
  transcript
FROM
  interviews
WHERE
  year = 2021
  AND month = 7
  AND day = 28
  AND transcript LIKE '%bakery%'
ORDER BY
  name;
-- Witnesses are-Eugene, Raymond, and Ruth.
-- Eugene gave pieces of information Thief was pulling out cash from the ATM on Leggett Street. In this way, checking the record number of the individual who did that exchange.
SELECT
  account_number,
  amount
FROM
  atm_transactions
WHERE
  year = 2021
  AND month = 7
  AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';
-- Observing the names related with the comparing account numbers. Placing these names in the 'Suspect List'
SELECT
  name,
  atm_transactions.amount
FROM
  people
  JOIN bank_accounts ON people.id = bank_accounts.person_id
  JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE
  atm_transactions.year = 2021
  AND atm_transactions.month = 7
  AND atm_transactions.day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';
-- Raymond gave hints - As leaving the bread kitchen, they called an individual and talked for under a moment. They requested the individual on the opposite end from the call to purchase a flight ticket of the earliest trip on July 29, 2021.
-- First tracking down the data about the aiport in Fiftyville which would be the beginning of the trip of the criminal.
SELECT
  abbreviation,
  full_name,
  city
FROM
  airports
WHERE
  city = 'Fiftyville';
-- Tracking down the trips on July 29 from Fiftyville air terminal, and requesting them by time.
SELECT
  flights.id,
  full_name,
  city,
  flights.hour,
  flights.minute
FROM
  airports
  JOIN flights ON airports.id = flights.destination_airport_id
WHERE
  flights.origin_airport_id = (
    SELECT
      id
    FROM
      airports
    WHERE
      city = 'Fiftyville'
  )
  AND flights.year = 2021
  AND flights.month = 7
  AND flights.day = 29
ORDER BY
  flights.hour,
  flights.minute;
-- First flight emerges to be at 8:20 to LaGuardia Airport in New York City (Flight id-36). This could be where the criminal went to.
-- Actually taking a look at the rundown of travelers in that flight. Putting them all in 'Suspect List'. Requesting the names as per their identification numbers.
SELECT
  passengers.flight_id,
  name,
  passengers.passport_number,
  passengers.seat
FROM
  people
  JOIN passengers ON people.passport_number = passengers.passport_number
  JOIN flights ON passengers.flight_id = flights.id
WHERE
  flights.year = 2021
  AND flights.month = 7
  AND flights.day = 29
  AND flights.hour = 8
  AND flights.minute = 20
ORDER BY
  passengers.passport_number;
-- Checking the call records to observe the individual who purchased the tickets.
-- Initially, really looking at the potential names of the guest, and placing these names in the 'Suspect List'. Requesting them as indicated by the spans of the calls.
SELECT
  name,
  phone_calls.duration
FROM
  people
  JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE
  phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration <= 60
ORDER BY
  phone_calls.duration;
-- Besides, really looking at the potential names of the call-collector. Requesting them as per the lengths of the calls.
SELECT
  name,
  phone_calls.duration
FROM
  people
  JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE
  phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration <= 60
ORDER BY
  phone_calls.duration;
-- Ruth gave pieces of information The criminal drove away in a vehicle from the pastry shop, in something like a little ways from the robbery. In this way, checking the tags of vehicles inside that time span. Then, at that point, looking at the names of those vehicles' proprietors. They could be suspects.
SELECT
  name,
  bakery_security_logs.hour,
  bakery_security_logs.minute
FROM
  people
  JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE
  bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.activity = 'exit'
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute >= 15
  AND bakery_security_logs.minute <= 25
ORDER BY
  bakery_security_logs.minute;
