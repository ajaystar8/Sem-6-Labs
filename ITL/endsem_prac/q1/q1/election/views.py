from django.shortcuts import render
from .models import CandidateModel, VotingModel

# Create your views here.
def candidates(request):
    candidate_list = CandidateModel.objects.all()
    return render(request, 'index.html', {'cand_list': candidate_list})
    
