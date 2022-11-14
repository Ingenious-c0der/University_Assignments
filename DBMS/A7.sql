create table Library(
    id int AUTO_INCREMENT NOT NULL primary key ,
    bookName varchar(30), 
    IssuerName varchar(20),
    Status varchar(1) , 
    DOI DATE 
);
create table Library_Audit(
    id int , 
    bookName varchar(30), 
    IssuerName varchar(20),
    Status varchar(1) , 
    DOI DATE 
);
delimiter // 
create trigger audit after insert on Library 
FOR EACH ROW 
begin 
    insert into Library_Audit values (NEW.id, NEW.bookName,NEW.IssuerName, NEW.Status, NEW.DOI) ; 
end ; 


create trigger up_aud before update on Library
 FOR EACH ROW 
begin 
    insert into Library_Audit values  (OLD.id, OLD.bookName, OLD.IssuerName, OLD.Status, OLD.DOI); 
end; //
delimiter ; 