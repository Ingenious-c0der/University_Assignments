create table Stud_Marks(
    name varchar(20), 
    total_marks INT 
) ; 

create table Result(
    RollNo INT, 
    Name  varchar(20), 
    Class varchar(30)
)


delimiter // 
create function getGrade( marks  INT)
returns varchar(30) deterministic  
begin 

IF(marks <= 1500 and marks >=990) THEN 
 return "Distinction" ;
ELSEIF (marks <= 989 and marks >=900) THEN 
 return "First Class"; 
ELSEIF (marks <= 899 and marks>= 825) THEN 
 return "Higher Second Class" ; 
END IF; 

return "No Class" ; 
END ; // 

create procedure proc_Grade(IN roll_No INT , IN sname VARCHAR(20))
BEGIN  
declare marks int default 0 ;
declare calc_class varchar(30) default "None" ;

declare exit handler for SQLSTATE '43250'
begin 
select "Roll No Should have a positive Value" as Exception; 
end ; 
declare exit handler for not found 
begin 
select "Student with given name not found" as Exception; 
end; 
  
IF (roll_No < 0 ) THEN 
SIGNAL SQLSTATE '43250'; 
END IF; 

select total_marks into marks from Stud_Marks where name = sname ;
select getGrade(marks) into calc_class ; 
insert into Result values(roll_No, sname ,calc_class) ; 
END ; //

delimiter // 
create procedure proc_All()
begin 
declare C int default 1 ; 
declare complete int default 0 ; 
declare sname varchar(30); 
declare stotal_marks int default 0 ; 
declare student_cursor CURSOR for Select * from Stud_Marks ; 
declare continue handler for not found 
begin 
set complete = 1 ;
end ;

OPEN student_cursor ; 
L:LOOP 
FETCH student_cursor into sname , stotal_marks; 

IF(complete = 1) THEN 
LEAVE L ;
END IF; 
call proc_Grade(C,sname); 
set C = C+1 ; 
END LOOP; 
CLOSE student_cursor; 
 
END ; //
delimiter ; 

