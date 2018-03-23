create database ssdriver;
use ssdriver;

create table devices (
    id varchar(30) primary key,
    devtype integer,
    section long,
    target integer,
    status integer,
    value float,
    unit integer
);

create table commands (
    id integer primary key,
    devtype integer,
    section long,
    target integer,
    onoff integer,
    ratio float
);
