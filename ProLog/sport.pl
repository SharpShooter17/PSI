/* tag::bazaFaktow[] */
jest(jan, pilkarz).
jest(marek, pilkarz).
jest(adam, plywak).
jest(jan, plywak).
jest(X, sportowiec) :- jest(X, plywak); biega(X).
/* end::bazaFaktow[] */

/* tag::reguly[] */
biega(X) :- jest(X, pilkarz).
bierze_udzial_w_zawodach(X) :- jest(X, sportowiec), ma_kondycje(X).
ma_kondycje(X) :- jest(X, pilkarz). 
/* end::reguly[] */