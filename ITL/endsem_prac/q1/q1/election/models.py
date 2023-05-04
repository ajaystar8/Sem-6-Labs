from django.db import models

# Create your models here.
class CandidateModel(models.Model):
    name = models.CharField(max_length = 150)
    section = models.CharField(max_length = 1, choices = [('A', 'A'), ('B', 'B'), ('C', 'C'), ('D', 'D')])

class VotingModel(models.Model):
    name = models.ForeignKey(CandidateModel, on_delete=models.CASCADE)
    vote = models.BooleanField()
