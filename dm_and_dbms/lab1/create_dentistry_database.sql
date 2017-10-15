DROP TABLE users;
DROP TABLE doctors;
DROP TABLE patients;
DROP TABLE dentistries;
DROP TABLE appointments;

CREATE TABLE users (
    user_id NUMBER(2) PRIMARY KEY,
    full_name VARCHAR2(25) NOT NULL,  
    birthdate DATE NOT NULL,
    address VARCHAR2(50) NOT NULL
);

COMMIT;

INSERT INTO users VALUES (1, 'Liam Smith', to_date('09-06-1973', 'dd-mm-yyyy'), '1637 Ella Street, Palo Alto, CA 94301');
INSERT INTO users VALUES (2, 'Noah Johnson', to_date('28-06-1984', 'dd-mm-yyyy'), '2037 Duck Creek Road, Palo Alto, CA 94306');
INSERT INTO users VALUES (3, 'Emma Williams', to_date('08-02-1969', 'dd-mm-yyyy'), '4963 Ella Street, Palo Alto, CA 94306');
INSERT INTO users VALUES (4, 'Olivia Brown', to_date('21-11-1987', 'dd-mm-yyyy'), '3977 Rardin Drive, Palo Alto, CA 94306');
INSERT INTO users VALUES (5, 'Ava Jones', to_date('17-07-1974', 'dd-mm-yyyy'), '598 Rardin Drive, Palo Alto, CA 94301');
INSERT INTO users VALUES (6, 'Lucas Miller', to_date('01-01-1989', 'dd-mm-yyyy'), '1873 Ella Street, Palo Alto, CA 94306');
INSERT INTO users VALUES (7, 'Mason Davis', to_date('25-08-1975', 'dd-mm-yyyy'), '1598 Thunder Road, Palo Alto, CA 94306');
INSERT INTO users VALUES (8, 'Logan Garcia', to_date('20-05-1983', 'dd-mm-yyyy'), '3013 Rardin Drive, Palo Alto, CA 94306');
INSERT INTO users VALUES (9, 'Isabella Rodriguez', to_date('05-08-1985', 'dd-mm-yyyy'), '2875 Burwell Heights Road, Palo Alto, CA 94302');
INSERT INTO users VALUES (10, 'Sophia Wilson', to_date('28-06-1984', 'dd-mm-yyyy'), '2227 Fairfield Road, Palo Alto, CA 94301');
INSERT INTO users VALUES (11, 'Mia Martinez', to_date('28-02-2001', 'dd-mm-yyyy'), '840 Mayo Street, Palo Alto, CA 94301');
INSERT INTO users VALUES (12, 'Oliver Anderson', to_date('18-08-1995', 'dd-mm-yyyy'), '4180 Wolf Pen Road, Palo Alto, CA 94301');
INSERT INTO users VALUES (13, 'Ethan Taylor', to_date('25-08-1975', 'dd-mm-yyyy'), '4594 Thunder Road, Palo Alto, CA 94301');
INSERT INTO users VALUES (14, 'Elijah Thomas', to_date('12-12-1998', 'dd-mm-yyyy'), '1295 Duck Creek Road, Palo Alto, CA 94306');
INSERT INTO users VALUES (15, 'Amelia Hernandez', to_date('25-04-1992', 'dd-mm-yyyy'), '1289 Ella Street, Palo Alto, CA 94301');
INSERT INTO users VALUES (16, 'Charlotte Moore', to_date('24-04-1971', 'dd-mm-yyyy'), '3584 Duck Creek Road, Palo Alto, CA 94301');
INSERT INTO users VALUES (17, 'Harper Martin', to_date('17-03-1991', 'dd-mm-yyyy'), '1471 Thunder Road, Palo Alto, CA 94301');
INSERT INTO users VALUES (18, 'Aiden Jackson', to_date('16-03-2012', 'dd-mm-yyyy'), '1352 Rardin Drive, Palo Alto, CA 94306');
INSERT INTO users VALUES (19, 'James Thompson', to_date('24-04-2013', 'dd-mm-yyyy'), '2135 Wolf Pen Road, Palo Alto, CA 94301');
INSERT INTO users VALUES (20, 'Benjamin White', to_date('16-03-2012', 'dd-mm-yyyy'), '3335 Thunder Road, Palo Alto, CA 94301');

COMMIT;

CREATE TABLE doctors (
    user_id NUMBER(2) PRIMARY KEY
);

COMMIT;

DECLARE
    user_id NUMBER := 1;
BEGIN
    FOR i IN 1..10 LOOP
        INSERT INTO doctors VALUES (user_id);
        user_id := user_id + 1;
    END LOOP;
    COMMIT;
END;
    
/

CREATE TABLE patients (
    user_id NUMBER(2) PRIMARY KEY,
    doctor_id NUMBER(2)
);

COMMIT;

DECLARE
    user_id NUMBER := 11;
    doctor_id NUMBER := 1;
BEGIN
    FOR i IN 1..10 LOOP
        INSERT INTO patients VALUES (user_id, doctor_id);
        user_id := user_id + 1;
        doctor_id := doctor_id + 1;
    END LOOP;
    COMMIT;
END;
    
/
    
CREATE TABLE dentistries (
    dentistry_id NUMBER(3) PRIMARY KEY,
    user_id NUMBER(2) NOT NULL,
    tooth_id NUMBER(2) NOT NULL,
    condition VARCHAR2(15)
);

COMMIT;

DECLARE
    x NUMBER := 1;
BEGIN
    FOR i IN 18..20 LOOP
        FOR j IN 1..32 LOOP
            INSERT INTO dentistries VALUES (x, i, j, 'milk');
            x := x + 1;
        END LOOP;
    END LOOP;
    FOR i IN 11..17 LOOP
        FOR j IN 1..32 LOOP
            INSERT INTO dentistries VALUES (x, i, j, 'permanent');
            x := x + 1;
        END LOOP;
    END LOOP;
    COMMIT;
END;

/
    
CREATE TABLE appointments (
    appointment_id NUMBER(2) PRIMARY KEY,
    patient_id NUMBER(2) NOT NULL,
    date_and_time DATE NOT NULL,
    doctor_id NUMBER(2),
    work_description VARCHAR2(100),  
    price NUMBER NOT NULL,
    payment_form VARCHAR2(10) NOT NULL
);

COMMIT;

INSERT INTO appointments VALUES (1, 11, to_date('25-09-2016 09:00', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 1', 100, 'cash');
INSERT INTO appointments VALUES (2, 12, to_date('25-09-2017 10:30', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 2', 550, 'card');
INSERT INTO appointments VALUES (3, 13, to_date('25-09-2017 12:00', 'dd-mm-yyyy hh24:mi'), 1, 'Work description 3', 200, 'card');
INSERT INTO appointments VALUES (4, 14, to_date('26-09-2017 09:30', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 4', 450, 'cash');
INSERT INTO appointments VALUES (5, 15, to_date('26-10-2017 10:00', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 5', 300, 'cash');
INSERT INTO appointments VALUES (6, 16, to_date('26-10-2017 11:30', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 6', 350, 'card');
INSERT INTO appointments VALUES (7, 11, to_date('27-10-2017 10:00', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 7', 400, 'cash');
INSERT INTO appointments VALUES (8, 18, to_date('27-10-2017 11:30', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 8', 250, 'card');
INSERT INTO appointments VALUES (9, 19, to_date('27-11-2017 13:00', 'dd-mm-yyyy hh24:mi'), NULL, 'Work description 9', 500, 'card');
INSERT INTO appointments VALUES (10, 14, to_date('28-11-2017 10:30', 'dd-mm-yyyy hh24:mi'), 2, 'Work description 10', 150, 'cash');

COMMIT;