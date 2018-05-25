mezczyzna(franciszek).
mezczyzna(jan).
mezczyzna(bogdan).
mezczyzna(wojciech).
mezczyzna(krzysztof).
mezczyzna(wojciech).
mezczyzna(robert).

kobieta(wanda).
kobieta(maria).
kobieta(anna).
kobieta(zofia).
kobieta(ewa).
kobieta(katarzyna).

maz(X) :- mezczyzna(X).
zona(X) :- kobieta(X).

rodzic(franciszek, maria).
rodzic(wanda, bogdan).
rodzic(jan, krzysztof).
rodzic(maria, krzysztof).
rodzic(jan, wojciech).
rodzic(maria, wojciech).
rodzic(bogdan, ewa).
rodzic(anna, ewa).
rodzic(bogdan, zofia).
rodzic(anna, zofia).
rodzic(wojciech, katarzyna).
rodzic(zofia, katarzyna).
rodzic(wojciech, robert).
rodzic(zofia, robert).

ojciec(X, Y) :- rodzic(X, Y), mezczyzna(X).
matka(X, Y) :- rodzic(X, Y), kobieta(X).

malzenstwo(wojciech, zofia).
malzenstwo(jan, maria).
malzenstwo(bogdan, anna).

dziadek(X, Z) :- ojciec(X, Y), rodzic(Y, Z).
babcia(X, Z) :- matka(X, Y), rodzic(Y, Z).

syn(X, Y) :- rodzic(Y, X), mezczyzna(X).
corka(X, Y) :- rodzic(Y, X), kobieta(X).

brat(X, Z) :- ojciec(Y, X), ojciec(Y, Z), mezczyzna(X).
siostra(X, Z) :- ojciec(Y, X), ojciec(Y, Z), kobieta(X).
