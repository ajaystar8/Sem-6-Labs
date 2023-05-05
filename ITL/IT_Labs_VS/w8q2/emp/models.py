from django.db import models

# Create your models here.
class WorksModel(models.Model):
    empid = models.PositiveIntegerField()
    pname = models.CharField(max_length = 100)
    cname = models.CharField(max_length = 100)
    salary = models.PositiveIntegerField()

    def __str__(self):
        return self.pname

class LivesModel(models.Model):
    empid = models.ForeignKey(WorksModel, on_delete = models.CASCADE)
    street = models.CharField(max_length = 100)
    city = models.CharField(max_length = 100)

    def __str__(self):
        return self.empid