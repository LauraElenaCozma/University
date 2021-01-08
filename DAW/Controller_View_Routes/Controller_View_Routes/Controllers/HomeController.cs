using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Controller_View_Routes.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }

        // /Home/ViewContent
        //to check Content of ActionResult
        public ActionResult ViewContent(int page, int nr)
        {
            //returns a blank page with the html content <h1>Hello</h1>
            return Content("<h1>Hello</h1><p>page</p><p>nr</p>");
        }

        [Route("AttributeRoute/{age:regex(^\\d{1,3}$):range(0, 120)}/{val?}")]
        public ActionResult AtributeRoutes(int age, int? val)
        {
            if (!val.HasValue)
                val = 0;
            return Content(String.Format("Age {0}, value {1}", age, val));
        }

    }
}