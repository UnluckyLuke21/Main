# Rabbit Population

import abc

class Rabbit(object):

    maxAge = {'F': 4, 'M': 3}               # Settings for the Population
    nRabbitPerBirth = {'F': 3, 'M': 2}      # Settings for the Population
    adults = {'nMales': 0, 'age': 1}        # Number of adult males in the Population and the age the Rabbits have to be to be official adult

    population = []

    def __init__(self):
        self.age = 0

    def yearAction(self):
        pass

    def endOfYear(self):
        self.age += 1

    @property
    @abc.abstractmethod
    def gender(self):
        raise NotImplementedError()

    @classmethod
    def genesis(cls):
        # TODO
        pass

    @classmethod
    def advanceOneYear(cls):
        for rabbit in cls.population:
            rabbit.yearAction()
        for rabbit in cls.population:
            rabbit.endOfYear()
        cls.concludeYear()

    @classmethod
    def concludeYear(cls):
        graveYard = []
        for rabbit in cls.population:
            if rabbit.age > cls.maxAge[rabbit.gender]:
                graveYard.append(rabbit)
        for rabbit in graveYard:
            cls.population.remove(rabbit)

    @classmethod
    def count(cls):
        # TODO
        pass

    @classmethod
    def stats(cls):
        # Return a dictionary with number of males and females, per age.
        dico = {'F': {}, 'M': {}}
        for rabbit in cls.population:
            try:
                dico[rabbit.gender][rabbit.age] += 1
            except KeyError:
                dico[rabbit.gender][rabbit.age] = 1
        return dico

#----------------------------------------------

class Female(Rabbit):

    def yearAction(self):
        # TODO
        pass

#----------------------------------------------

class Male(Rabbit):

    def __del__(self):
        # TODO
        pass

    def endOfYear(self):
        # TODO
        pass

class Female(Rabbit):
    
    def yearAction(self):
        #TODO
        pass

class Male(Rabbit):

    def __del__(self):
        #TODO
        pass

    def endOfYear(self):
        #TODO
        pass

#-------------------------------------------------

if __name__ == '__main__':
    nYears = 7
    popEvol = []

    print('Running rabbit simulator')
    Rabbit.genesis() # Entstehung
    for n in range(nYears):
        print(f' -- year {n+1}')
        print(Rabbit.stats())
        Rabbit.advanceOneYear()
        popEvol.append(Rabbit.count())
    print('-- evolution over the years (F, M) :')
    print(popEvol)