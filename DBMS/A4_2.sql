
-- in older versions declare float value as FLOAT(40 ,5 ) => FLOAT(Size , decimal places tracked)

create table areas (
    radius FLOAT , 
    area FLOAT 
); 

delimiter // 
create procedure calc_area(IN radius FLOAT)
begin
declare calculated_area FLOAT default 0.0 ; 
declare exit handler for SQLSTATE '42350'
begin 
select "The radius should be in between 5 and 9 " as Exception; 
end ; 
IF(radius > 5 and radius < 9) THEN 
set calculated_area = 3.14 * radius * radius ; 
insert into areas values ( radius , calculated_area) ;
select calculated_area as "Calculated Area" ; 
ELSE 
 SIGNAL SQLSTATE '42350' ;
END IF ;
END ; 
//
delimiter ; 
 
