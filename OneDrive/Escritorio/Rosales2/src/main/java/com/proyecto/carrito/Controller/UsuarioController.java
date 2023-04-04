package com.proyecto.carrito.Controller;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import com.proyecto.carrito.model.Cliente;
import com.proyecto.carrito.model.Transaccion;
import com.proyecto.carrito.service.IUsuarioInterface;
import com.proyecto.carrito.service.OrdenService;

import jakarta.servlet.http.HttpSession;

@Controller
@RequestMapping("/Cliente")

public class UsuarioController {

	private final Logger logger=LoggerFactory.getLogger(UsuarioController.class);
	
	@Autowired
	private IUsuarioInterface usuarioService;
	
	//@Autowired
	private OrdenService ordenService;
	
	@GetMapping("/registro")
	public String create() {
		return "Cliente/registro";
	}
	
	@PostMapping("/save")
	public String save(Cliente usuario) {
		
		logger.info("Usuario registro:{}",usuario);
		usuario.setTipo("USER");
		//usuarioService.save(usuario);
		return "redirect:/";
	}
	
	@GetMapping("/login")
	public String login() {
	    return "Cliente/login";
	}
	
	@PostMapping("/acceder")
	public String acceder(Cliente usuario) {
		 logger.info("Accesos:{}",usuario);
		 
		
		return "redirect:/";
		
	}
	
	@GetMapping("/compras")
	public String obtenerCompra(HttpSession session,Model model) {
      model.addAttribute("sesion", session.getAttribute("idusuario"));
		
		Cliente usuario= usuarioService.findById(  Integer.parseInt(session.getAttribute("idusuario").toString()) ).get();
		List<Transaccion> ordenes= ordenService.findByUsuario(usuario);
		logger.info("ordenes {}", ordenes);
		
		model.addAttribute("ordenes", ordenes);
		
		return "usuario/compras";
	
	
	
	}
	
}
