use theater;

--impossible

set transaction isolation level read uncommitted;

begin transaction;

update actor set name_middle = N'Петров' where id = 2

commit;

