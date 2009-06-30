from django.conf import settings
from django.shortcuts import render_to_response, get_object_or_404
from django.template import RequestContext
from django.contrib.auth.models import User
from django.http import HttpResponse, HttpResponseForbidden

from django.utils.translation import ugettext_lazy as _
from django.utils.translation import ugettext

from fritzing.apps.user_profile.models import Profile
from fritzing.apps.user_profile.forms import ProfileForm

if "notification" in settings.INSTALLED_APPS:
    from notification import models as notification
else:
    notification = None

def profiles(request, template_name="user_profile/profiles.html"):
    return render_to_response(template_name, {
        "users": User.objects.all().order_by("-date_joined"),
    }, context_instance=RequestContext(request))

def profile(request, username, template_name="user_profile/profile.html"):
    other_user = get_object_or_404(User, username=username)
    if request.user.is_authenticated():
        if request.user == other_user:
            is_me = True
        else:
            is_me = False
    else:
        is_me = False
    
    if is_me:
        if request.method == "POST":
            if request.POST["action"] == "update":
                profile_form = ProfileForm(request.POST, instance=other_user.get_profile())
                if profile_form.is_valid():
                    profile = profile_form.save(commit=False)
                    profile.user = other_user
                    profile.save()
            else:
                profile_form = ProfileForm(instance=other_user.get_profile())
        else:
            profile_form = ProfileForm(instance=other_user.get_profile())
    else:
        profile_form = None

    return render_to_response(template_name, {
        "profile_form": profile_form,
        "is_me": is_me,
        "other_user": other_user,
    }, context_instance=RequestContext(request))