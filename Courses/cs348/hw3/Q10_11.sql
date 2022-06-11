DELIMITER $$
DROP PROCEDURE IF EXISTS store_procedure;

CREATE PROCEDURE store_procedure(IN student_id int, OUT average_gpa int, OUT above_average_count int)

BEGIN

SELECT AVG(grade) INTO average_gpa
FROM Grades
WHERE sid=student_id;

SELECT COUNT(grade) INTO above_average_count
FROM Grades g1
WHERE sid=student_id
AND grade > (
            SELECT AVG(grade) as grade
            FROM Grades g2
            WHERE g1.cid=g2.cid
            GROUP BY cid);

END

DELIMITER ;

DELIMITER $$
DROP TRIGGER IF EXISTS after_insert_grade;

CREATE TRIGGER after_insert_grade
AFTER INSERT ON Grades
FOR EACH ROW
BEGIN

DECLARE avg_cs INT;
DECLARE student_id INT;

SELECT INSERTED.sid INTO student_id
       FROM INSERTED;

SELECT AVG(Grades.grade) INTO avg_cs FROM Grades
INNER JOIN Courses ON Grades.cid=Courses.cid
WHERE sid=student_id AND Courses.cname LIKE 'CS%'
GROUP BY sid;

IF EXISTS (SELECT sid FROM Scholarship WHERE sid=student_id)
    IF avg_cs <= 90 THEN
        DELETE FROM Scholarship WHERE sid=student_id;
    END IF;
ELSE
    IF avg_cs >= 90 THEN
        INSERT INTO Scholarship VALUES(student_id, 2021);
    END IF;
END IF;

END


DELIMITER ;
