-- 1.
SELECT date_and_time, user_id, full_name, birthdate, address, permanent_doctor
FROM appointments a JOIN (
SELECT user_id, full_name, birthdate, address, doctor_id AS permanent_doctor
FROM users JOIN patients USING(user_id)
) p ON a.patient_id = p.user_id 
WHERE date_and_time >= to_date('26-09-2017', 'dd-mm-yyyy') AND date_and_time < to_date('27-09-2017 ', 'dd-mm-yyyy')
    
-- 2.
SELECT *
FROM users JOIN patients USING(user_id)
WHERE user_id NOT IN (
SELECT patient_id
FROM appointments
WHERE doctor_id IS NOT NULL
)
    
-- 3.
SELECT TO_CHAR(date_and_time, 'Month') AS month_of_2017_year, SUM(price) AS revenue
FROM appointments
WHERE EXTRACT(year FROM date_and_time) = 2017
GROUP BY TO_CHAR(date_and_time, 'Month')
ORDER BY TO_DATE(month_of_2017_year, 'Month')
