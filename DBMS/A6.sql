create table O_Table (
name varchar(30),
salary int
);

create table N_Table( 
id int AUTO_INCREMENT NOT NULL , 
name varchar(40),
salary int, 
primary key(id)
);

delimiter //  
create procedure migrate()
begin 
declare total int default 0 ; 
declare done int default FALSE ;
declare o_name varchar(30) default ""; 
declare o_salary int default 0 ; 
declare o_cursor CURSOR for select * from O_Table; 
declare continue handler for not found SET done = 1 ;

open o_cursor ; 
migration_loop : LOOP 

FETCH o_cursor into o_name, o_salary; 
IF( done = 1) THEN 
LEAVE migration_loop ;
END IF ;
select name from N_Table where name = o_name ;
IF (o_name not in (select name from N_Table)) THEN 
-- this can be bulk shown by storing in some variable if you don't like
-- showing it after each migration 
select CONCAT("Migrating " , o_name , "to new table") as "Information" ; 
insert into N_Table values (default, o_name, o_salary) ; 
set total = total + 1 ;
END IF ;
END LOOP ; 
CLOSE o_cursor; 
select "OLD TABLE MIGRATED TO NEW TABLE SUCCESSFULLY" as "Message",total as "Total Employees Migrated";
end ; //
delimiter ; 





insert into O_Table VALUES ('Sagarw',500000);

insert into O_Table VALUES ('Yashwad',530000);

insert into O_Table VALUES ('Vikaswdad',100000);

insert into O_Table VALUES ('Kshitijwdad',30000);

insert into O_Table VALUES ('Aryanwdad',17000);

insert into O_Table VALUES ('Jaydwad',232342);

insert into O_Table VALUES ('Virajeawdan',3245565);

insert into O_Table VALUES ('Rohitwdad',223233);

insert into O_Table VALUES ('Atharvaawd',7347347);

insert into N_Table VALUES (default , 'Jay',232342) ; 

insert into N_Table VALUES (default ,'Kshitij',30000) ; 

insert into N_Table VALUES (default , 'Atharva',7347347) ; 