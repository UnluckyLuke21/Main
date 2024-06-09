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

    @classmethod
    def genesis(cls):
<<<<<<< HEAD
        pass
=======
        # TODO
        cls.population.append(Male())
        cls.population.append(Female())
>>>>>>> 4c1f26f5a6c3d7f3b27821100e008932d5b588fa

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
        # Count Females and Males:
        dico = [0, 0]
        for rabbit in cls.population:
            if rabbit.gender == 'F':
                dico[0] += 1
            if rabbit.gender == 'M':
                dico[1] += 1
        return dico

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

    def __init__(self):
<<<<<<< HEAD
=======
        Rabbit.__init__(self)
>>>>>>> 4c1f26f5a6c3d7f3b27821100e008932d5b588fa
        self.gender = 'F'

    def yearAction(self):

        if self.age < 1:
            return

        if self.age > 4:
            return

        for i in range (Rabbit.nRabbitPerBirth['F']):
            Rabbit.population.append(Female())

        Rabbit.population.append(Male())
        Rabbit.population.append(Male())

        # TODO Giving birth
        # Reading Info how many Rabbits they should be:
        # Female Rabbits:
        
        #print(f'Gave Birth to {fem} Feamel Rabbits and {mal} Rabbits')

#----------------------------------------------

class Male(Rabbit):

    def __init__(self):
<<<<<<< HEAD
        self.gender = 'M'

    def __del__(self):
        # TODO
        pass

    def endOfYear(self):
        # TODO
=======
        Rabbit.__init__(self)
        self.gender = 'M'

    def __del__(self):
        #TODO
>>>>>>> 4c1f26f5a6c3d7f3b27821100e008932d5b588fa
        pass

#-------------------------------------------------

if __name__ == '__main__':
    nYears = 7
    popEvol = []

    print('Running rabbit simulator')
    Rabbit.genesis()
    for n in range(nYears):
        print(f' -- year {n+1}')
        print(Rabbit.stats())
        Rabbit.advanceOneYear()
        popEvol.append(Rabbit.count())
    print('-- evolution over the years (F, M) :')
    print(popEvol)