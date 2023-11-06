-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check interviews from 2021/7/28
select * from interviews where month = 7 and day = 28;

-- Check cars at bakery within 10 minutes from robbery (2021/7/28 10:15am)
select * from bakery_security_logs where day = 28 and month = 7 and hour = 10;
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55

-- find atm transactions before the robbery
select * from atm_transactions where day = 28 and month = 7 and year = 2021 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';
--  246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35

--find phone calls day of that last under a minute
select name from people where phone_number in (select caller from phone_calls where day = 28 and month = 7 and duration < 60);
--  221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
-- +-----+----------------+----------------+------+-------+-----+----------+

--find earliest flight next day
 select * from airports where city = "Fiftyville";
--  | id | abbreviation |          full_name          |    city    |
-- +----+--------------+-----------------------------+------------+
-- | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |

select * from flights where day = 29 and month = 7 and year = 2021 and origin_airport_id = 8 order by hour asc;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
-- | 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
-- | 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

select * from airports where id = 4;
-- +----+--------------+-------------------+---------------+
-- | id | abbreviation |     full_name     |     city      |
-- +----+--------------+-------------------+---------------+
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+--------------+-------------------+---------------+

--find person whose phone number, license plate and passport number, bank number all match with
select name from people where license_plate in (select license_plate from bakery_security_logs where day = 28 and month = 7 and hour = 10 and activity = 'exit' and minute between 15 and 25) and phone_number in (select caller from phone_calls where day = 28
   ...> and month = 7 and duration < 60) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where day = 28 and month = 7 and year = 2021 and atm_location = 'Leggett Street' and transaction_type = 'withdraw'))
   ...>  and passport_number in (select passport_number from passengers where flight_id = 36);
;
-- Thief is Bruce
-- Bruce took flight 36 to NYC

-- find accomplice
select name from people where phone_number in (select receiver from phone_calls where caller in (select phone_number from people where name = 'Bruce') and day = 28 and month = 7 and duration < 60);

-- Robin is the accomplice