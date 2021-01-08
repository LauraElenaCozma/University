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

        // /AttributeRoute/23/1
        [Route("AttributeRoute/{age:regex(^\\d{1,3}$):range(0, 120)}/{val?}")]
        public ActionResult AtributeRoutes(int age, int? val)
        {
            if (!val.HasValue)
                val = 0;
            return Content(String.Format("Age {0}, value {1}", age, val));
        }

        /*Sa se creeze o ruta care contine in ea doi parametri de tip string si care acceseaza o metoda ce
        afiseaza daca unul din ei este continut ca string in celalalt.*/
        [Route("StringInString/{s1}/{s2}")]
        public ActionResult StringContainsAnother(String s1, String s2)
        {
            if (s1.Contains(s2))
                return Content(String.Format("{0} contains {1}", s1, s2));
            else if (s2.Contains(s1))
                return Content(String.Format("{0} contains {1}", s2, s1));
            else return Content("No string contains the another string!");
        }

        /*2. Sa se modifice comportamentul rutei anterioare astfel incat al doilea parametru sa fie optional; sa
        se afiseze un mesaj in cazul in care acesta nu este prezent.*/
        public ActionResult StringContainsAnotherOptional(String s1, String s2)
        {
            if (s2 != null)
            {
                if (s1.Contains(s2))
                    return Content(String.Format("{0} contains {1}", s1, s2));
                else if (s2.Contains(s1))
                    return Content(String.Format("{0} contains {1}", s2, s1));
                else return Content("No string contains the another string!");
            }
            else return HttpNotFound("The second string is missing!");
        }

        /*Sa se creeze o ruta cu un parametru ale carui valori posibile sa fie numere naturale pare ce au intre 3 si 7 cifre.*/
        public ActionResult EvenNumberCustom(int? nr)
        {
            //daca nu putem UrlParameter.Optional in ruta, nu va intra pe al doilea caz
            if(nr != null)
            {
                return Content(String.Format("The number is {0}", nr));
            }
            return HttpNotFound("Missing nr parameter!");
        }

        [Route("numberAttribute/{nr:regex(^[1-9]\\d{1,5}[02468]$)?}")]
        public ActionResult EvenNumberAttribute(int? nr)
        {
            if (nr != null)
            {
                return Content(String.Format("The number is {0}", nr));
            }
            return HttpNotFound("Missing nr parameter!");
        }

        /*4. Sa se creeze un view partial ce primeste un argument un numar intreg si afiseaza daca este divizibil
        cu 7 si un view care primeste ca argument o lista de numere, iar pentru fiecare numar din lista, il
        afiseaza si apeleaza view-ul partial cu numarul respectiv drept argument.*/
        public ActionResult ListOfNumbers()
        {
            List<int> list = new List<int> { 10, 21, 32, 43, 54, 65 };
            return View(list);
        }
    }
}