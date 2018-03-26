create user ssdriver@localhost identified by 'sssample';
create user ssdriver@'%' identified by 'sssample';

create database sssample;

grant all privileges on sssample.* to ssdriver@'%';
grant all privileges on sssample.* to ssdriver@localhost;
flush privileges;

use sssample;

create table devices (
    id varchar(30) primary key,
    devtype integer,
    section bigint,
    target integer,
    status integer,
    value float,
    unit integer
);

create table commands (
    id integer primary key auto_increment,
    devtype integer,
    section bigint,
    target integer,
    onoff integer,
    ratio float
);
