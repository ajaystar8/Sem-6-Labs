from django.db import models

# Create your models here.
class HumanModel(models.Model):
    fname = models.CharField(max_length = 100)
    lname = models.CharField(max_length = 100)
    phone = models.PositiveIntegerField()
    addr = models.TextField()
    city = models.CharField(max_length = 100)
