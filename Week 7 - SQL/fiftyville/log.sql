-- Keep a log of any SQL queries you execute as you solve the mystery.

Suspects:

|  License Plate suspects  |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey

Caller Suspects:
 Sofia   |
| Kelsey  |
| Bruce   |
| Kelsey  |
| Taylor  |
| Diana   |
| Carina  |
| Kenny   |
| Benista

  Withdraw Suspects:  |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |

 Passengers  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca

If we look at all charts Bruce is the only one that appears in all 4 lists.
The accomplice is Robin because thats who Bruce was calling
Bruce destination was New York City


Background:

the mystery of the stolen duck. Authorities believe that the thief stole the duck and then, shortly afterwards,
took a flight out of town with the help of an accomplice.

Your goal is to identify:

Who the thief is,
What city the thief escaped to, and
Who the thief’s accomplice is who helped them escape
All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

QUERIES:


1.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2021
AND street = "Humphrey Street";

Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time –
each of their interview transcripts mentions the bakery.

2.
SELECT transcript
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2021;

| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by
the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
 The thief then asked the person on the other end of the phone to purchase the flight ticket.                                                                        |
| I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.

3.
SELECT activity, license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND year = 2021
AND hour = 10 AND minute >= 5 AND minute <=25
AND activity = "exit";

Got 8 license plates numbers to pop up leaving between 10 and 10:30 which can be matched to people

4.
SELECT name FROM people
JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
WHERE month = 7 AND day = 28 AND year = 2021
AND hour = 10 AND minute >= 5 AND minute <=25
AND activity = "exit";

License plate associate with:

|  name   |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey

5.
SELECT transcript FROM interviews
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN interviews ON interviews.name = people.name
WHERE month = 7 AND day = 28 AND year = 2021
AND hour = 10 AND minute >= 5 AND minute <=25
AND activity = "exit";

6.
SELECT caller, receiver FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2021
AND duration < 60;

callers that day:
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131


7.
SELECT name FROM people
JOIN phone_calls on phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND year = 2021
AND duration < 60;

 Sofia   |
| Kelsey  |
| Bruce   |
| Kelsey  |
| Taylor  |
| Diana   |
| Carina  |
| Kenny   |
| Benista


8.
SELECT name FROM people
JOIN phone_calls on phone_calls.receiver = people.phone_number
WHERE month = 7 AND day = 28 AND year = 2021
AND duration < 60;

 Jack       |
| Larry      |
| Robin      |
| Melissa    |
| James      |
| Philip     |
| Jacqueline |
| Doris      |
| Anna

9.
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2021
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";

Got bunch of account numbers

10.
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE month = 7 AND day = 28 AND year = 2021
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";

People who withdrew money on that day

  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |

11.

Passengers passport number to people passport
start with airport

SELECT full_name, id FROM airports
WHERE city = "Fiftyville";


Fiftyville Regional Airport id 8

12.

Select id, hour, minute FROM flights
WHERE origin_airport_id = 8
AND month = 7 AND day = 29 AND year = 2021;

 id | hour | minute |
+----+------+--------+
| 18 | 16   | 0      |
| 23 | 12   | 15     |
| 36 | 8    | 20     |
| 43 | 9    | 30     |
| 53 | 15   | 20     |

Earliest flight is 8:20 and ID is 36

13.

SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE flight_id = 36;


 name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca

14. --this an equivalent way to combine all three previous searches

SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN (
Select id FROM flights
WHERE month = 7 AND day = 29 AND year = 2021
AND origin_airport_id = (
SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1);

15.
SELECT city FROM airports
JOIN flights on flights.destination_airport_id = airports.id
WHERE flights.id = 36;

     city      |
+---------------+
| New York City







