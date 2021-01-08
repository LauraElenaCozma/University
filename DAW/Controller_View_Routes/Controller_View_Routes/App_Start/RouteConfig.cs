using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Controller_View_Routes
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapMvcAttributeRoutes();

            routes.MapRoute(
                name: "ContainsStringOptional",
                url: "StringInStringOptional/{s1}/{s2}",
                defaults: new { controller = "Home", action = "StringContainsAnotherOptional", s2 = UrlParameter.Optional });
            /*routes.MapRoute(
                name: "MyCustomRoute",
                url: "RouteCustom/{page}/{nr}",
                defaults: new { controller = "Home", action = "ViewContent" });*/
            routes.MapRoute(
                name: "EvenNumberCustom",
                url: "number/{nr}",
                defaults: new { controller = "Home", action = "EvenNumberCustom", nr = UrlParameter.Optional },
                new {nr= @"^[1-9]\d{1,5}[02468]$" });
            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );
        }
    }
}
