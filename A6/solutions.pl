% Problem 1

% Facts
parent(bart,homer).
parent(bart,marge).
parent(lisa,homer).
parent(lisa,marge).
parent(maggie,homer).
parent(maggie,marge).
parent(homer,abraham).
parent(herb,abraham).
parent(tod,ned).
parent(rod,ned).
parent(marge,jackie).
parent(patty,jackie).
parent(selma,jackie).
female(maggie).
female(lisa).
female(marge).
female(patty).
female(selma).
female(jackie).
male(bart).
male(homer).
male(herb).
male(burns).
male(smithers).
male(tod).
male(rod).
male(ned).
male(abraham).

% Relationship 
% not(X=Y)
brother(X,Y) :- parent(X,Z), parent(Y,Z), male(Y), \==(X,Y).
sister(X,Y) :- parent(X,Z), parent(Y,Z), female(Y), \==(X,Y).
aunt(X,Y) :- female(Y), parent(X,Z), sister(Z,Y).
uncle(X,Y) :- male(Y), parent(X,Z), brother(Z,Y).
grandfather(X,Y) :- male(Y), parent(X,Z), parent(Z,Y).
granddaughter(X,Y) :- female(Y), parent(Y,Z), parent(Z,X).
ancestor(X,Y) :- parent(X,Y); parent(X,Z), parent(Z,Y).
unrelated(X,Y) :- \+brother(X,Y), \+sister(X,Y), \+aunt(X,Y), \+uncle(X,Y), \+grandfather(X,Y), \+granddaughter(X,Y), \+ancestor(X,Y).


% Problem 2

% Facts
occupation(joe,oral_surgeon).
occupation(sam,patent_laywer).
occupation(bill,trial_laywer).
occupation(cindy,investment_banker).
occupation(joan,civil_laywer).
occupation(len,plastic_surgeon).
occupation(lance,heart_surgeon).
occupation(frank,brain_surgeon).
occupation(charlie,plastic_surgeon).
occupation(lisa,oral_surgeon).
address(joe,houston).
address(sam,pittsburgh).
address(bill,dallas).
address(cindy,omaha).
address(joan,chicago).
address(len,college_station).
address(lance,los_angeles).
address(frank,dallas).
address(charlie,houston).
address(lisa,san_antonio).
salary(joe,50000).
salary(sam,150000).
salary(bill,200000).
salary(cindy,140000).
salary(joan,80000).
salary(len,70000).
salary(lance,650000).
salary(frank,85000).
salary(charlie,120000).
salary(lisa,190000).

% Additional rules
/*
cityOfState(houston,Texas).
cityOfState(dallas,Texas).
cityOfState(college_station,Texas).
cityOfState(san_antonio,Texas).
cityOfState(pittsburgh,Pennsylvania).
cityOfState(chicago,Illonis).
cityOfState(omaha,Nebraska).
cityOfState(los_angeles,California).
*/

isTexas(houston).
isTexas(dallas).
isTexas(college_station).
isTexas(san_antonio).

isSurgeon(heart_surgeon).
isSurgeon(plastic_surgeon).
isSurgeon(oral_surgeon).

/* X=person, Y=money, Z=city, A=job */
query(X) :- salary(X,Y), Y >= 100000, address(X,Z), isTexas(Z), occupation(X,A), isSurgeon(A).
% cityOfState(Z,Zs), Zs == Texas


% Problem 3

% Facts

subject(algebra,math).
subject(calculus,math).
subject(dynamics,physics).
subject(electromagnetism,physics).
subject(nuclear,physics).
subject(organic,chemistry).
subject(inorganic,chemistry).

degree(bill,phd,chemistry).
degree(john,bs,math).
degree(chuck,ms,physics).
degree(susan,phd,math).

retired(bill).

canTeach(X,Y) :- degree(X,D,Z), subject(Y,Z), D==phd.

canTeach2(X,Y) :- degree(X,D,Z), subject(Y,Z), (D==phd ; D==ms).

canTeach3(X,Y) :- degree(X,D,Z), subject(Y,Z), (D==phd ; D==ms), \+retired(X).



% Problem 4
countdown(0).
countdown(N) :- N>0,format('~w~n',[N]),M is N-1,countdown(M).

% wrapper function adds 3rd arg
/*countup(A,B) :- A<B,countup(A,B,C). % <initial counter value>*/
countup(A,B) :- A=<B,countup(A,B,A).
% countup(A,B,C) :- C=B,format('~w~n',[C]).
/* what is the base case? The last part of the or statement*/
/*  what is the recursive case? The first part of the or statment*/
countup(A,B,C) :- (C<B,format('~w~n',[C]),C2 is C+1,countup(A,B,C2));(C=B,format('~w~n',[C])).

% implement countup 3 different ways

/*First, you can try switching the order of the calls to format and the recursive call in the antecedents of a rule like countdown.*/
countup1(A,B) :- (A<B,V is B-1,countup1(A,V),format('~w~n',[B]));(A=B,format('~w~n',[A])).


/* Second, you can try mimicking countdown, but print B-C*/
countup2(A,B,C) :- (B2 is B-C,C>0,format('~w~n',[B2]),C2 is C-1,countup2(A,B,C2));(C=0, format('~w~n',[B])) .
countup2(A,B) :- A=<B,C is B-A,countup2(A,B,C).

/* Third, you can change the recursion to count upward (by incrementing the count argument until it reaches B). */
countup3(A,B) :- A=<B,countup(A,B,A).
countup3(A,B,C) :- (C<B,format('~w~n',[C]),C2 is C+1,countup(A,B,C2));(C=B,format('~w~n',[B])).
countup4(A,B) :- (A<B,format('~w~n',[A]),V is A+1,countup1(V,B));(A=B,format('~w~n',[B])).
